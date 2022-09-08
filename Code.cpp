/*        Your Name & E-mail: Angelica Simityan   asimi003@ucr.edu

 *         Discussion Section: 021

 *         Assignment: Lab # 2 Exercise # 3

 *         Exercise Description: [optional - include for your own benefit]

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link:
          https://youtu.be/DJ_Om9Vch1A

 */

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
int X=8;
int Y=9;
//int PrevStateX=LOW;
//int PrevStateY=HIGH;
int valueX = 0;
int valueY = 1;

// Serial Monitor Buffer
int s_buf = 0x00;

/* 's' is an array of integers of size 8. Note that arrays start at 0
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)

// Read from the serial monitor into s_buf and the s[] array for individual bits
void readData()
{
    if(Serial.available())
        s_buf = Serial.parseInt();

    for(int i = (s_size - 1); i>=0; i--)  {
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting
        // "&" bit masking
    }

}
// Reset the Output Buffer.
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}

void setup() {
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
     pinMode(X,INPUT);
     pinMode(Y,INPUT_PULLUP);
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    resetBuffer();
    // Note that here we arbitrarily connect b_buf & s_buf together. The important point is that we preserve the current value of the output buffer into a variable b_buf before writing it to the pins. If we resetBuffer or readData() again, we still know the values the output is set to, because it is in b_buf.
    
    if(digitalRead(X) == HIGH || valueX == 1)
    {
       valueX = 1;
       valueY = 1;
       //PrevStateX=digitalRead(X);
       b_buf = analogRead(A0);
       b_buf = map(b_buf, 0, 1023, 0, 15);
       writeBuffer(b_buf);
    }
    else if(digitalRead(Y) == LOW || valueY == 0){
       valueY = 0;
       valueX = 0;
       //PrevStateY=digitalRead(Y);
       b_buf = 1023-analogRead(A0);
       b_buf = map(b_buf, 0, 1023, 0, 15);
       writeBuffer(b_buf);
    }
}
