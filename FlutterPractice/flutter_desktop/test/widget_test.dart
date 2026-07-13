import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

import 'package:flutter_desktop/main.dart';

void main() {
  testWidgets('Desktop content renders', (WidgetTester tester) async {
    await tester.pumpWidget(
      const MaterialApp(home: SafeArea(child: MyScaffold())),
    );

    expect(find.text('Header'), findsOneWidget);
    expect(find.text('Hello, world!'), findsOneWidget);
    expect(find.text('Hello, android!'), findsOneWidget);
    expect(find.text('Hello, flutter!'), findsOneWidget);
  });
}
