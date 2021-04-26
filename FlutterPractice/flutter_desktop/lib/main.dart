import 'package:flutter/material.dart';

void main() {
  runApp(MaterialApp(
    title: 'Hello, Flutter',
    home: SafeArea(child: MyScaffold()),
  ));
}

class MyAppBar extends StatelessWidget {
  MyAppBar({this.title});

  final Widget title;

  @override
  Widget build(BuildContext context) {
    return Container(
      height: 56.0,
      padding: const EdgeInsets.symmetric(horizontal: 8.0),
      decoration: BoxDecoration(color: Colors.grey[500]),
      child: Row(
        children: <Widget>[
          IconButton(icon: Icon(Icons.menu_rounded), tooltip: 'Navigation menu', onPressed: null),
          Expanded(child: title),
          IconButton(icon: Icon(Icons.settings_rounded), tooltip: 'Settings', onPressed: null),
        ],
      ),
    );
  }
}

class MyScaffold extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Material(
      child: Column(
        children: <Widget>[
          MyAppBar(title: Text('Header', style: Theme.of(context).primaryTextTheme.headline6)),
          Expanded(
              child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Center(child: Text('Hello, world!')),
              Center(child: Text('Hello, world!')),
              Center(child: Text('Hello, world!')),
            ],
          )),
        ],
      ),
    );
  }
}
