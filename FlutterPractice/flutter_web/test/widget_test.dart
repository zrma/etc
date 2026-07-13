// This is a basic Flutter widget test.
//
// To perform an interaction with a widget in your test, use the WidgetTester
// utility that Flutter provides. For example, you can send tap and scroll
// gestures. You can also use WidgetTester to find child widgets in the widget
// tree, read text, and verify that the values of widget properties are correct.

import 'package:flutter_test/flutter_test.dart';

import 'package:flutter_web/main.dart';

void main() {
  testWidgets('Navigation changes the selected content', (
    WidgetTester tester,
  ) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(const MyApp());

    expect(find.text('Index 0: Call'), findsOneWidget);
    expect(find.text('Index 1: Message'), findsNothing);

    await tester.tap(find.text('Message').last);
    await tester.pump();

    expect(find.text('Index 0: Call'), findsNothing);
    expect(find.text('Index 1: Message'), findsOneWidget);
  });
}
