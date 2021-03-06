
/*
1、最初にLEDを押すー＞カウントスタート、テストモード
2、1分以上スイッチに触らないと、カウントスタート
3、一度でも、カウントボタンに触れると2に移動する
4、15分後、大容量起動。
*/

const int led_pin = 13; // LED connected to digital pin 13
const int sw_pin = 2; // switch pin connected to digital pin 2
const int big_pin = 6;
int sw_state = LOW; // switch state
// HIGH: sw is closed
// LOW:  sw is open

// global var
int waiting_time = 0;
int bimyo_time=0;

//config
int limit_time = 60;
int spark_time = 19 * 60;

void setup()
{
    pinMode(led_pin, OUTPUT); // 13番のデジタルLED
    pinMode(sw_pin, INPUT); //スイッチ
    pinMode(big_pin, OUTPUT); //大容量出力
}

void loop()
{
    // put your main code here, to run repeatedly:
    sw_state = digitalRead(sw_pin); // read the switch state
    if (sw_state == HIGH) {
      if(waiting_time ==0){
        digitalWrite(led_pin, LOW); // sets the LED on
      }else if(bimyo_time>2){
        waiting_time = 0;
        bimyo_time=0;
        digitalWrite(led_pin, LOW); // sets the LED on
      }else{
        bimyo_time=bimyo_time+1;
      }
      
    }
    else {
        bimyo_time=0;
        waiting_time = waiting_time + 1;
        if (waiting_time >= limit_time) {
            int i = spark_time / 2;
            while (i > 0) {
                if (i % 30 == 0) {
                    int i2 = 10;
                    while (i2 > 0) {
                        digitalWrite(led_pin, HIGH); // sets the LED off
                        delay(100); // waits for a second
                        digitalWrite(led_pin, LOW); // sets the LED on
                        delay(100);
                        i2 = i2 - 1;
                    }
                }
                else {
                    digitalWrite(led_pin, HIGH); // sets the LED off
                    delay(1000); // waits for a second
                    digitalWrite(led_pin, LOW); // sets the LED on
                    delay(1000);
                }
                i = i - 1;
            }

            i = 3;
            while (i > 0) {
                digitalWrite(led_pin, HIGH); // sets the LED off
                delay(150); // waits for a second
                digitalWrite(led_pin, LOW); // sets the LED on
                delay(150);
                i = i - 1;
            }

            while (true) {
                digitalWrite(big_pin, HIGH);
                digitalWrite(led_pin, HIGH);
                delay(100);
                digitalWrite(big_pin, LOW);
                digitalWrite(led_pin, LOW);
                delay(300);
                digitalWrite(big_pin, HIGH);
                digitalWrite(led_pin, HIGH);
                delay(150);
                digitalWrite(big_pin, LOW);
                digitalWrite(led_pin, LOW);
                delay(300);
            }
        }
        digitalWrite(led_pin, HIGH); // sets the LED off
    }

    delay(1000);
}
