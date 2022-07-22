import 'package:flutter/material.dart';
import 'dart:io';
import 'package:intl/intl.dart';
import 'dart:async';
import 'package:timetn/timetncalc.dart';
import 'package:auto_size_text/auto_size_text.dart';

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
  bool? persistentValue = true;
  bool? showWhenLockedValue = true;
  final String persistentNotification = 'Persistent notification';
  final String showTimeWhenLocked = 'Show time when phone is locked';
  String timeNowText = '';
  String timeNow = '21:34:56';

  @override
  void initState() {
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
    });
  }

  String _formatDateTime(DateTime dateTime) {
    return DateFormat('hh:mm:ss').format(dateTime);
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
            colorFilter: ColorFilter.mode(Colors.white38, BlendMode.difference),
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
                  color: const Color.fromARGB(255, 0, 94, 122).withOpacity(1),
                  fontSize: 40,
                ),
                minFontSize: 18,
                maxLines: 1,
                overflow: TextOverflow.ellipsis,
              ),
              Text(
                timeNow,
                style: TextStyle(
                  color: const Color.fromARGB(255, 0, 0, 0).withOpacity(0.4),
                  fontSize: 18,
                ),
              ),
              const SizedBox(height: 50),
              CheckboxListTile(
                title: Text(persistentNotification),
                value: persistentValue,
                onChanged: (newValue) {
                  setState(() {
                    persistentValue = newValue;
                  });
                },
                controlAffinity: ListTileControlAffinity.leading,
              ),
              CheckboxListTile(
                title: Text(showTimeWhenLocked),
                value: showWhenLockedValue,
                onChanged: (newValue) {
                  setState(() {
                    showWhenLockedValue = newValue;
                  });
                },
                controlAffinity: ListTileControlAffinity.leading,
              ),
            ],
          ),
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _exitApp,
        tooltip: 'Exit',
        child: const Icon(Icons.close_outlined),
      ),
    );
  }
}
