/*

Developed under Arduino 1.5.6-r2 for Arduino DUE only
necessary parts: 
1 Arduino DUE
1 STS spectromer connected to 5V, GND and via MAX-RS232 chip to Serial1 RX/TX
1 RTC DS1307 connected to 5V, GND and via I²C to pin 20(SDA) and pin 21(SCL) adress 0x68
1 SD Shield or similar with SD card 
1 Status LED connected to pin 13 and GND (optional)

This code will do the following:
1. System check (if something does not work, the status LED will blink wildly)
2. Write a line to the startup logfily SPECYLOG.CSV
3. Create folder of the current date (eg. 141116 = Year 2014, Month 11, Day 16)
4. Optimize the STS spectrometers integration time to the current light conditions
5. Saves a spectrum to the folder in a file named after the startup time (eg. 142211 = Hour 14, Minute 22, Secon 11)
...Continues with step 5 forever
If light conditions change significantly, it will optimize integration time again
If 1000 measurements were stored in a file, it will create a new file
*/


//teensy to do list
//write code to accept the incoming bytes from this sketch as status indicators from experiment
// downlink that

#include "Wire.h" //necessary for the RTC
#include "SD.h" //for using the SD card
#include "SPI.h" //for using the SD card library
byte commandByte = 0x00;
const int spectrum_length = 1024;
byte STS_binning = 1;  //this sketch only works with binning of 1, don´t change!

byte spectrum[spectrum_length]; //array to store the byte output of the STS
int  spectrum_count = 0; //stores the number of saved bytes
unsigned long cycle_number = 1; //how many measurement cycles have been performed since startup
unsigned long int_time = 1000000; //in µseconds
unsigned long max_int_time = 2000000;  //maximum integration time allowed (the absolute maximum is 10 s)
unsigned long spec_every_sec = 1;  //save a spec every X seconds, set to 0 to save spectra as fast as possible
unsigned long last_spec = 0;  //saves the time when the last spectrum was taken

char current_path[8];  //folder to save the measurements (date)
char current_file_name[18]; //name of the file, including the folder  eg.: 141118/123412.csv

File SDcard;

//Status LED Pin
byte LED = 13;

//system check variables:
boolean STS_ok = false;
boolean SD_ok = false;
boolean do_optimise = true;

void setup() {
  Wire.begin();
  Serial.begin(57600); //we use the serial interface to see whats going on
  Serial2.begin(9600);
  Serial.println(getTimeRTCScreen());

  pinMode(LED, OUTPUT);
  blink_wildly(1000);

  initialise_STS(STS_binning); //checks if the STS is working properly and intialises the STS on Serial1 and sets speed to 115200 BAUD and binning to 1

  initialise_SD();  //checks if the SD card is inserted and creates a line in the SPECYLOG.csv
  Serial.println(set_dir_and_file());  //Set´s the directory according to the date and the file where the spectra should be saved according to the time
  Serial.println("Ready");
  blink_wildly(1000);
}

void loop() { //everything inside the loop is repeated forever
 while(Serial2.available())
 {
    commandByte = Serial2.read();
    hasp_processcmd(commandByte);
    commandByte = 0x00;
 }

 
  if (do_optimise) {
    STS_optimise_it();
    do_optimise = false;
  }

  if (last_spec + (spec_every_sec * 1000) < millis()) {
    last_spec = millis();

    STS_get_full_spectrum();

    digitalWrite(LED, HIGH);
    save_to_sd();   //saves the spectrum and metadata to the SD card
    digitalWrite(LED, LOW);
    cycle_number++;

    int peak_val = STS_find_peak();  //search for the highest value of the last spectrum
    if ((peak_val > 15000) || (peak_val < 13000)) { //whenever the peak value is out of the optimum area, optimize again
      do_optimise = true;
      Serial.println("optimizing");
    }

    if (cycle_number % 1000 == 0) { //prevent files from getting to large -> every 1000 measurements start a new file
      //setup a new measurement file
      Serial.print(getTimeRTCScreen());
      Serial.println(" New Measurement File");
      Serial.println(set_dir_and_file());
    }
  }

bool start = experiment();
if(start == true)
{
  runExperiment();
}


}//loop end

void runExperiment()
{
  //science sequence here
  /* create new file, log 1000 times over some time, create new file, run experiment procedure, log again, close file.*/
}

void blink_wildly(int ms) {
  unsigned long start_time = millis();
  while (start_time + ms > millis()) {
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(50);
  }
}
//on the way up, log a spectrum every several minutes. on experiment begin, close that file and begin experiment. will end with three files. 



