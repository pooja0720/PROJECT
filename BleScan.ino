#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int ledPin=7;
int RSSI_CUTOFF=-60;

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  
}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");


  int bestDev=RSSI_CUTOFF;
  BLEAdvertisedDevice bestDevice=results.getDevice(1);


  for (int i = 0; i <foundDevices.getCount(); i++)
  {
     BLEAdvertisedDevice device = results.getDevice(i);
     int rssi = device.getRSSI();
     if (rssi > bestDev) {
       best = rssi;
       BLEAdvertisedDevice bestDevice=results.getDevice(i);
    }
  }
  Serial.println("Nearby device :");
  Serial.println(bestDevice.getName());

  if (bestDevice.getRSSI()>RSSI_CUTOFF)
  {
      digitalWrite(ledPin,HIGH);
  }else{
      digitalWrite(ledPin,LOW);
  }
  

  pBLEScan->clearResults();   
  delay(2000);
}