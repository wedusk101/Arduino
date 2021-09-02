#include <math.h>

#define SIZE 5
#define SCALE 8 // scale exponent with base 2 - i.e. actual scale is 2^SCALE

unsigned long MAX_LOOP = 200000;

int listFixed[SIZE];
float listFloat[SIZE];

float productFloat = 1.0f;
unsigned long productFixed = 1;

int floatToFixed(float x)
{
  return (x * (1 << SCALE));
}

float fixedToFloat(int x)
{
  return (float)x / (float)(1 << SCALE);
}

void testFloatToFixed()
{
  float x = 3.5;
  int y = floatToFixed(3.5);
  float z = fixedToFloat(y);

  Serial.println("\nTesting floating point to fixed point conversions...");
  Serial.println("x and z should be equal (or nearly so) for the test to pass.");
  Serial.print("x (float): ");
  Serial.println(x);  
  Serial.print("y (x float to fixed): ");
  Serial.println(y);
  Serial.print("z (y fixed to float): ");
  Serial.println(z);
}

unsigned long mulFixed(unsigned long x , unsigned long y)
{
  return ((unsigned long) x * (unsigned long) y) >> SCALE;
}

void testMulFixed()
{
  float x = 3.5;
  float y = 1.2;
  float xyFloat = x * y;

  int xFixed = floatToFixed(x);
  int yFixed = floatToFixed(y);
  int xyFixed = mulFixed(xFixed, yFixed);

  float xyFixedToFloat = fixedToFloat(xyFixed);

  Serial.println("\nTesting fixed point multiplication...");
  Serial.println("xyFloat and xyFixedToFloat should be equal (or nearly so) for the test to pass.");
  Serial.print("x (float): ");
  Serial.println(x);  
  Serial.print("y (x float to fixed): ");
  Serial.println(y);
  Serial.print("xyFloat: ");
  Serial.println(xyFloat);  
  Serial.print("xyFixed: ");
  Serial.println(xyFixed);
  Serial.print("xyFixedToFloat: ");
  Serial.println(xyFixedToFloat);
}

void displayList(int* arr)
{
  Serial.println("Printing the list of integers...");
  
  for (unsigned int i = 0; i < SIZE; ++i)
    Serial.println(arr[i]);
}

void displayList(float* arr)
{
  Serial.println("Printing the list of floats...");
  
  for (unsigned int i = 0; i < SIZE; ++i)
    Serial.println(arr[i], 2);
}

void multiplyFloat(float *arr)
{
  float prod = 1.0;
  for (unsigned long i = 0; i < MAX_LOOP; ++i)
  {
    prod = 1.0f;
    for (unsigned int j = 0; j < SIZE; ++j) 
      if (arr[j] > 0.0f)
        prod *= arr[j];
  }

  productFloat = prod;
}

void multiplyFixed(int *arr)
{
  unsigned long prod = 1;
  for (unsigned long i = 0; i < MAX_LOOP; ++i)
  {
    prod = 1;
    for (unsigned int j = 0; j < SIZE; ++j) 
      if (arr[j] > 0)
        prod = mulFixed(prod, arr[j]);
  }

  productFixed = prod;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  Serial.println("Generating random floats...");

  randomSeed(analogRead(0));  
  for (unsigned int i = 0; i < SIZE; ++i)
    listFloat[i] = random(1, 100) / 10.0f;

  displayList(listFloat);

  Serial.println("Getting product using floating point arithmetic...");

  unsigned long startTimeFloat = millis();

  multiplyFloat(listFloat);

  unsigned long stopTimeFloat = millis();  

  Serial.print("The product is: ");
  Serial.println(productFloat, 2);
  Serial.println("Time taken in ms: ");
  Serial.println(stopTimeFloat - startTimeFloat);


  //////////////////////////////////////////////////////////////////////////////////////

  // testFloatToFixed();
  // testMulFixed();

  Serial.println("Processing list...");

  for (unsigned int i = 0; i < SIZE; ++i)
    listFixed[i] = floatToFixed(listFloat[i]);

  displayList(listFixed);
  
  Serial.println("Getting product using fixed point arithmetic...");

  unsigned long startTimeFixed = millis();

  multiplyFixed(listFixed);

  unsigned long stopTimeFixed = millis();  

  Serial.print("The product is: ");
  Serial.println(fixedToFloat(productFixed), 2);
  Serial.println("Time taken in ms: ");
  Serial.println(stopTimeFixed - startTimeFixed);
}

void loop() {

}
