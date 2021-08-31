#include <math.h>

#define SIZE 10
#define SCALE 8 // scale exponent with base 2 - i.e. actual scale is 2^SCALE

#define FLOAT_TO_FIXED(x) (x >> SCALE)

unsigned long MAX_LOOP = 200000;

int listFixed[SIZE];
float listFloat[SIZE];

float product = 1.0f;

void multiplyFloat(float *arr)
{
  float prod = 1.0;
  for (unsigned long i = 0; i < MAX_LOOP; i++)
  {
    prod = 1.0f;
    for (unsigned int j = 0; j < SIZE; j++) 
      if (arr[j] > 0.0f)
        prod *= arr[j];
  }

  product = prod;
}

void multiplyFixed(int *arr)
{
  
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  Serial.println("Generating random floats...");

  randomSeed(analogRead(0));  
  for (unsigned int i = 0; i < SIZE; i++)
    listFloat[i] = random(1, 100) / 10.0f;

  Serial.println("Printing the list of random floats...");
  for (unsigned int i = 0; i < SIZE; i++)
    Serial.println(listFloat[i], 2);

  Serial.println("Getting product using floating point arithmetic...");

  unsigned long startTimeFloat = millis();

  multiplyFloat(listFloat);

  unsigned long stopTimeFloat = millis();  

  Serial.print("The product is: ");
  Serial.println(product, 2);
  Serial.println("Time taken in ms: ");
  Serial.println(stopTimeFloat - startTimeFloat);

  //////////////////////////////////////////////////////////////////////////////////////

  Serial.println("Processing list...");

  for (unsigned int i = 0; i < SIZE; i++)
  {
    
  }
  
  Serial.println("Getting product using fixed point arithmetic...");

  unsigned long startTimeFixed = millis();

  multiplyFixed(listFixed);

  unsigned long stopTimeFixed = millis();  

  Serial.print("The product is: ");
  Serial.println(product, 2);
  Serial.println("Time taken in ms: ");
  Serial.println(stopTimeFixed - startTimeFixed);
}

void loop() {

}
