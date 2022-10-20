#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);

  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.println("ligado");
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);

  Serial.println("desligado");
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}