import 'package:flutter/material.dart';
import 'dart:io';

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
  String timeNow = 'الأربعة و درجين ما حررش';

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
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              timeNow,
              style: Theme.of(context).textTheme.headline5,
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
      floatingActionButton: FloatingActionButton(
        onPressed: _exitApp,
        tooltip: 'Exit',
        child: const Icon(Icons.close_outlined),
      ),
    );
  }
}
