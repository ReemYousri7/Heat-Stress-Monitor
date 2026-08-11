
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() => runApp(HeatStressApp());

class HeatStressApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Heat Stress Monitor',
      theme: ThemeData(primarySwatch: Colors.deepOrange),
      home: PredictionPage(),
    );
  }
}

class PredictionPage extends StatefulWidget {
  @override
  _PredictionPageState createState() => _PredictionPageState();
}

class _PredictionPageState extends State<PredictionPage> {
  final heartCtrl = TextEditingController(text: "75");
  final spo2Ctrl = TextEditingController(text: "98");
  final bodyCtrl = TextEditingController(text: "36.5");
  final ambCtrl = TextEditingController(text: "30");

  String result = "";
  bool loading = false;

  Future<void> sendPredict() async {
    setState(() { loading = true; result = ""; });
    final payload = {
      "heart_rate": double.parse(heartCtrl.text),
      "spo2": double.parse(spo2Ctrl.text),
      "body_temp": double.parse(bodyCtrl.text),
      "ambient_temp": double.parse(ambCtrl.text)
    };
    try {
      final uri = Uri.parse("http://10.0.2.2:5000/predict"); // emulator
      final resp = await http.post(uri,
        headers: {"Content-Type": "application/json"},
        body: json.encode(payload));
      if (resp.statusCode == 200) {
        final jsonResp = json.decode(resp.body);
        setState(() {
          result = "Class: ${jsonResp['prediction']['class']}\\nLabel: ${jsonResp['prediction']['label']}";
        });
      } else {
        setState(() { result = "Error ${resp.statusCode}: ${resp.body}"; });
      }
    } catch (e) {
      setState(() { result = "Exception: $e"; });
    } finally {
      setState(() { loading = false; });
    }
  }

  @override
  void dispose() {
    heartCtrl.dispose();
    spo2Ctrl.dispose();
    bodyCtrl.dispose();
    ambCtrl.dispose();
    super.dispose();
  }

  Widget buildInput(String label, TextEditingController ctrl) {
    return TextField(
      controller: ctrl,
      keyboardType: TextInputType.numberWithOptions(decimal: true),
      decoration: InputDecoration(labelText: label),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Heat Stress Monitor')),
      body: Padding(
        padding: EdgeInsets.all(16),
        child: Column(
          children: [
            buildInput("Heart Rate (bpm)", heartCtrl),
            buildInput("SpO2 (%)", spo2Ctrl),
            buildInput("Body Temp (°C)", bodyCtrl),
            buildInput("Ambient Temp (°C)", ambCtrl),
            SizedBox(height: 12),
            ElevatedButton(
              onPressed: loading ? null : sendPredict,
              child: loading ? CircularProgressIndicator(color: Colors.white) : Text("Predict"),
            ),
            SizedBox(height: 20),
            Text("Result:", style: TextStyle(fontWeight: FontWeight.bold)),
            SizedBox(height: 8),
            SelectableText(result),
          ],
        ),
      ),
    );
  }
}
