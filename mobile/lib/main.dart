import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'dart:io';
import 'package:intl/intl.dart';
import 'dart:async';
import 'package:timetn/timetncalc.dart';
import 'package:auto_size_text/auto_size_text.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:flutter/foundation.dart';
import 'dart:ui' as ui;

void main() {
  runApp(const TimeTN());
}

class TimeTN extends StatefulWidget {
  const TimeTN({Key? key}) : super(key: key);
  @override
  State<TimeTN> createState() => _TimeTNState();
}

class _TimeTNState extends State<TimeTN> {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Time TN',
      theme: ThemeData(
        primarySwatch: Colors.amber,
        fontFamily: 'Noto Kufi Arabic',
      ),
      home: const MyHomePage(title: 'الوقت بالتونسي'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;
  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late SharedPreferences prefs;
  late bool? persistentValue = true;
  late bool? showWhenLockedValue = true;
  final String persistentNotification = 'Persistent notification';
  final String showTimeWhenLocked = 'Show time when phone is locked';
  String timeNowText = '';
  String timeNow = '21:34:56';

  savePrefs() async {
    prefs = await SharedPreferences.getInstance();
    prefs.setBool('Persitent Notification', persistentValue ?? false);
    prefs.setBool('Show When Locked', showWhenLockedValue ?? false);
  }

  loadPrefs() async {
    prefs = await SharedPreferences.getInstance();
    setState(() {
      persistentValue = prefs.getBool('Persitent Notification') ?? true;
      showWhenLockedValue = prefs.getBool('Show When Locked') ?? true;
    });
  }

  @override
  void initState() {
    loadPrefs();
    timeNow = _formatDateTime(DateTime.now());
    Timer.periodic(const Duration(seconds: 1), (Timer t) => _getTime());
    super.initState();
  }

  void _getTime() {
    final DateTime now = DateTime.now();
    final String formattedDateTime = _formatDateTime(now);
    setState(() {
      timeNow = formattedDateTime;
      timeNowText = TimeTnCalc.eval(timeNow);
      //timeNowText = TimeTnCalc.eval('14:48:00');
      //timeNowText = TimeTnCalc.eval('23:00:00');
    });
  }

  String _formatDateTime(DateTime dateTime) {
    return DateFormat('HH:mm:ss').format(dateTime);
  }

  void _exitApp() {
    setState(() {
      exit(0);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text(widget.title),
          centerTitle: true,
        ),
        body: Container(
          padding: const EdgeInsets.all(20),
          decoration: const BoxDecoration(
            image: DecorationImage(
              image: AssetImage("assets/images/fond.png"),
              colorFilter:
                  ColorFilter.mode(Colors.white38, BlendMode.difference),
              repeat: ImageRepeat.repeat,
            ),
          ),
          child: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                AutoSizeText(
                  timeNowText,
                  style: TextStyle(
                    color: const Color.fromARGB(255, 0, 0, 0).withOpacity(1),
                    fontSize: 40,
                  ),
                  textAlign: TextAlign.center,
                  minFontSize: 10,
                  maxLines: 2,
                  overflow: TextOverflow.ellipsis,
                ),
                Text(
                  timeNow,
                  style: TextStyle(
                    color: const Color.fromARGB(255, 0, 0, 0).withOpacity(0.4),
                    fontSize: 18,
                  ),
                  textDirection: ui.TextDirection.rtl,
                ),
                const SizedBox(height: 50),
                Visibility(
                  visible: !kIsWeb,
                  child: CheckboxListTile(
                    title: Text(persistentNotification),
                    value: persistentValue,
                    onChanged: (newValue) {
                      setState(() {
                        persistentValue = newValue;
                      });
                      savePrefs();
                    },
                    controlAffinity: ListTileControlAffinity.leading,
                  ),
                ),
                Visibility(
                  visible: !kIsWeb,
                  child: CheckboxListTile(
                    title: Text(showTimeWhenLocked),
                    value: showWhenLockedValue,
                    onChanged: (newValue) {
                      setState(() {
                        showWhenLockedValue = newValue;
                      });
                      savePrefs();
                    },
                    controlAffinity: ListTileControlAffinity.leading,
                  ),
                ),
              ],
            ),
          ),
        ),
        floatingActionButton:
            Column(mainAxisAlignment: MainAxisAlignment.end, children: [
          Visibility(
            visible: true,
            child: FloatingActionButton(
              onPressed: () =>
                  Clipboard.setData(ClipboardData(text: timeNowText)),
              tooltip: 'Copy',
              child: const Icon(Icons.copy),
            ),
          ),
          const SizedBox(height: 5),
          Visibility(
            visible: !kIsWeb,
            child: FloatingActionButton(
              onPressed: _exitApp,
              tooltip: 'Exit',
              child: const Icon(Icons.close_outlined),
            ),
          )
        ]));
  }
}
