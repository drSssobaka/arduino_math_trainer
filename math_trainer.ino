#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad_I2C.h>
#include <Keypad.h>

#define keypad_I2CADDR 0x38

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, keypad_I2CADDR, PCF8574 );
LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x3f for a 16 chars and 2 line display

void setup()
{
	Wire.begin( );
	kpd.begin( makeKeymap(keys) );
	lcd.begin();                      // initialize the lcd 
	// Print a message to the LCD.
	lcd.backlight();
}


void loop()
{
	hello();
	int correct = 0;
	int wrong = 0;
	String answer = "";
	int seed = analogRead(A0);
	randomSeed(seed);
	
	bool continue_training_loop = true;
	
	//training loop
	while(continue_training_loop){
		answer = "";
		int num1 = random(99);
		int num2 = random(99);
		int sum = num1 + num2;
		bool continue_kpd_loop = true;
		char key = 0;
		
		//kpd loop
		while(continue_kpd_loop){
			draw_main_display(correct, wrong, num1, num2, answer);
			
			key = kpd.waitForKey();
			
			if((key >= '0') &&  (key <= '9')){
				answer += key;
			}
			else if(key == 'D'){
				int len = answer.length();
				if(len > 0)answer.remove(len - 1);
			}
			else if((key == '#') || (key == 'B')){
				continue_kpd_loop = false;
			}
		}  //end of kpd loop
		
		if(key == 'B') continue_training_loop = false;
		else if(key == '#'){
			int sum_answer = answer.toInt();
			if(sum == sum_answer) correct++;
			else wrong++;
		}
	}  // end of training loop
	
	goodbye(correct, wrong);
	while(true){}
}

void hello()
{
	lcd.clear();
	lcd.print(" TRAINER E32pr6 ");
	lcd.setCursor(0,1);
	lcd.print("sjris.l,293kcprl");
	delay(3000);  
}

void draw_main_display(int correct, int wrong, int num1, int num2, String answer)
{
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("corr:   wrng:");
	lcd.setCursor(5,0);
	lcd.print(correct);
	lcd.setCursor(13,0);
	lcd.print(wrong);
	lcd.setCursor(0,1);
	lcd.print("  +  =");
	lcd.setCursor(0,1);
	lcd.print(num1);
	lcd.setCursor(3,1);
	lcd.print(num2);
	lcd.setCursor(6,1);
	lcd.print(answer);
}

void goodbye(int correct, int wrong)
{
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Correct:");
	lcd.setCursor(9,0);
	lcd.print(correct);
	lcd.setCursor(0,1);
	lcd.print("Wrong:");
	lcd.setCursor(7,1);
	lcd.print(wrong);
	delay(3000);

lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("    GOODBYE!");
	
}