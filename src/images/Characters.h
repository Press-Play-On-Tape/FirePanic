#pragma once

namespace Images {

  const unsigned char PROGMEM Ambulance[] = {
  31, 31,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xbc, 0x82, 0x85, 0x81, 0xbd, 0x82, 0x3c, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0x01, 0xfc, 0x85, 0xfd, 0x01, 0xff, 0x03, 0xfd, 0xbd, 0xdd, 0xed, 0xbd, 0x9d, 0x85, 0xfd, 0x03, 0xff, 0x03, 0x05, 0xbd, 0xdd, 0xad, 0x3c, 0x38, 0x03, 0x04, 0xf8, 0x00, 
  0x00, 0x00, 0xff, 0x00, 0x82, 0xb2, 0x4a, 0xbb, 0xbb, 0xbb, 0xba, 0x7a, 0xfa, 0xca, 0xce, 0x86, 0x86, 0xce, 0xcb, 0xfb, 0x7b, 0xba, 0xba, 0xba, 0xb2, 0x6a, 0xe2, 0xea, 0x00, 0xff, 0x00, 
  0x06, 0x09, 0x0a, 0x16, 0x11, 0x16, 0x23, 0x41, 0x4c, 0x44, 0x41, 0x23, 0x16, 0x11, 0x13, 0x13, 0x13, 0x13, 0x11, 0x16, 0x23, 0x41, 0x4c, 0x44, 0x41, 0x23, 0x16, 0x11, 0x17, 0x08, 0x07, 
  };

  const unsigned char PROGMEM Ambulance_Mask[] = {
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x06, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x0f, 0x07, 
  };

  const unsigned char PROGMEM Ambulance_Lights_01[] = {
  11, 4,
  0x08, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x08, 
  };

  const unsigned char PROGMEM Ambulance_Lights_02[] = {
  11, 4,
  0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 
  };

  const unsigned char PROGMEM Ambulance_Door[] = {
  9, 31,
  0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0x00, 0xfe, 0x02, 0xf4, 0x09, 0xf2, 
  0x00, 0x00, 0xff, 0x0a, 0xfb, 0x8a, 0xaa, 0xca, 0x7b, 
  0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x03, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Ambulance_Door_Mask[] = {
  0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x01, 0x00, 
  };

  const unsigned char PROGMEM Victim_OnEdge[] = {
  34, 11,
  0xc0, 0x20, 0x20, 0x10, 0xd0, 0xd0, 0x50, 0x18, 0x04, 0x02, 0x81, 0x61, 0x41, 0x82, 0x9c, 0x60, 0x00, 0x7c, 0x82, 0x6c, 0x82, 0x7c, 0x82, 0xaa, 0x7c, 0x82, 0xbc, 0x7c, 0x82, 0x6a, 0x14, 0x5c, 0xa2, 0x5c, 
  0x00, 0x01, 0x01, 0x07, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_OnEdge_Mask[] = {
  0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0x7f, 0x7f, 0xfe, 0xfc, 0x60, 0x00, 0x7c, 0xfe, 0x7c, 0xfe, 0x7c, 0xfe, 0xfe, 0x7c, 0xfe, 0xfc, 0x7c, 0xfe, 0x7e, 0x1c, 0x5c, 0xfe, 0x5c, 
  0x00, 0x01, 0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_01[] = {
  16, 15,
  0xc0, 0x20, 0x20, 0x10, 0x7c, 0xc2, 0x81, 0x09, 0x19, 0x1a, 0x69, 0x36, 0x88, 0x90, 0x90, 0x60, 
  0x00, 0x31, 0x49, 0x49, 0x45, 0x32, 0x0a, 0x08, 0x08, 0x08, 0x05, 0x05, 0x09, 0x12, 0x09, 0x06, 
  };

  const unsigned char PROGMEM Victim_01_Mask[] = {
  0xc0, 0xe0, 0xe0, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xf6, 0xf8, 0xf0, 0xf0, 0x60, 
  0x00, 0x31, 0x79, 0x79, 0x7d, 0x3f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x0f, 0x1e, 0x0f, 0x06, 
  };

  const unsigned char PROGMEM Victim_02[] = {
  16, 15,
  0x0e, 0x11, 0x11, 0xe6, 0x08, 0x30, 0x0f, 0x31, 0x19, 0x0b, 0x8c, 0xc8, 0x08, 0x10, 0xe0, 0x00, 
  0x00, 0x00, 0x10, 0x29, 0x46, 0x50, 0x2e, 0x38, 0x43, 0x46, 0x35, 0x0b, 0x04, 0x05, 0x02, 0x00, 
  };

  const unsigned char PROGMEM Victim_02_Mask[] = {
  16, 15,
  0x0e, 0x1f, 0x1f, 0xfe, 0xf8, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0x00, 
  0x00, 0x00, 0x10, 0x39, 0x7f, 0x7f, 0x2f, 0x3f, 0x7f, 0x7f, 0x3f, 0x0b, 0x07, 0x07, 0x02, 0x00, 
  };

  const unsigned char PROGMEM Victim_03[] = {
  16, 15,
  0x30, 0xc8, 0xa4, 0xc8, 0x50, 0x50, 0x08, 0x08, 0x08, 0xa8, 0xa6, 0x51, 0x49, 0x49, 0x46, 0x80, 
  0x03, 0x04, 0x04, 0x08, 0x36, 0x4b, 0x2d, 0x4c, 0x48, 0x40, 0x21, 0x1f, 0x04, 0x02, 0x02, 0x01, 
  };

  const unsigned char PROGMEM Victim_03_Mask[] = { 
  0x30, 0xf8, 0xbc, 0xf8, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xfe, 0xdf, 0xcf, 0xcf, 0xc6, 0x80, 
  0x03, 0x07, 0x07, 0x0f, 0x37, 0x7f, 0x3f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x07, 0x03, 0x03, 0x01, 
  };

  const unsigned char PROGMEM Victim_04[] = {
  16, 15,
  0xa0, 0x50, 0x10, 0xe8, 0xd6, 0x31, 0x61, 0x0e, 0x3a, 0x05, 0x31, 0xca, 0x04, 0x00, 0x00, 0x00, 
  0x03, 0x04, 0x08, 0x09, 0x18, 0x68, 0x4c, 0x46, 0x78, 0x06, 0x08, 0x33, 0x44, 0x44, 0x38, 0x00, 
  };

  const unsigned char PROGMEM Victim_04_Mask[] = {
  0xa0, 0xf0, 0xf0, 0xe8, 0xfe, 0xff, 0xff, 0xfe, 0xfa, 0xff, 0xff, 0xce, 0x04, 0x00, 0x00, 0x00, 
  0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x07, 0x0f, 0x3f, 0x7c, 0x7c, 0x38, 0x00, 
  };

  const unsigned char PROGMEM Victim_05[] = {
  16, 15,
  0x00, 0x30, 0xc8, 0x84, 0x02, 0x02, 0x22, 0xb4, 0x52, 0x3c, 0xc8, 0x08, 0x30, 0xc0, 0x00, 0x00, 
  0x16, 0x29, 0x24, 0x1e, 0x08, 0x10, 0x20, 0x20, 0x23, 0x2d, 0x16, 0x16, 0x17, 0x11, 0x11, 0x0e, 
  };

  const unsigned char PROGMEM Victim_05_Mask[] = {
  0x00, 0x30, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfc, 0x7e, 0x3c, 0xf8, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 
  0x16, 0x3f, 0x3f, 0x1f, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e, 
  };

  const unsigned char PROGMEM Victim_06[] = {
  16, 15,
  0x00, 0xc6, 0x29, 0x1a, 0x0d, 0x09, 0x02, 0x8c, 0x04, 0xc2, 0x82, 0x04, 0x88, 0x70, 0x00, 0x00, 
  0x00, 0x03, 0x3c, 0x42, 0x4e, 0x5d, 0x33, 0x24, 0x25, 0x12, 0x13, 0x0e, 0x02, 0x01, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_06_Mask[] = {
  0x00, 0xc6, 0xef, 0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfc, 0xf8, 0x70, 0x00, 0x00, 
  0x00, 0x03, 0x3f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3c, 0x3d, 0x1f, 0x1f, 0x0f, 0x03, 0x01, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_07[] = {
  16, 15,
  0x38, 0x44, 0xc4, 0x74, 0x34, 0xb4, 0x5a, 0x62, 0x82, 0x02, 0x04, 0x08, 0xbc, 0x92, 0x4a, 0x34, 
  0x00, 0x00, 0x01, 0x06, 0x08, 0x09, 0x1e, 0x25, 0x16, 0x22, 0x20, 0x20, 0x10, 0x09, 0x06, 0x00, 
  };

  const unsigned char PROGMEM Victim_07_Mask[] = {
  0x38, 0x7c, 0xfc, 0xfc, 0xfc, 0xfc, 0x7e, 0x7e, 0xfe, 0xfe, 0xfc, 0xf8, 0xfc, 0xfe, 0x7e, 0x34, 
  0x00, 0x00, 0x01, 0x07, 0x0f, 0x0f, 0x1e, 0x3f, 0x1f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f, 0x06, 0x00, 
  };

  const unsigned char PROGMEM Victim_08[] = {
  16, 15,
  0x00, 0x40, 0xa0, 0x38, 0xe4, 0xa4, 0x52, 0x92, 0x66, 0x5d, 0x39, 0x21, 0x1e, 0xe0, 0x00, 0x00, 
  0x00, 0x07, 0x08, 0x10, 0x20, 0x21, 0x10, 0x18, 0x20, 0x48, 0x58, 0x2c, 0x4a, 0x31, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_08_Mask[] = {
  0x00, 0x40, 0xe0, 0xf8, 0xfc, 0xfc, 0xde, 0x9e, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 
  0x00, 0x07, 0x0f, 0x1f, 0x3f, 0x3f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f, 0x3f, 0x7b, 0x31, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_01[] = {
  12, 5,
  0x00, 0x04, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x04, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_01_Mask[] = {
  0x00, 0x1c, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x07, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_02[] = {
  12, 5,
  0x00, 0x00, 0x08, 0x02, 0x00, 0x08, 0x02, 0x00, 0x08, 0x02, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_02_Mask[] = {
  0x00, 0x1c, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x07, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_03[] = {
  12, 5,
  0x00, 0x00, 0x02, 0x08, 0x00, 0x02, 0x08, 0x00, 0x02, 0x08, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Victim_Halo_03_Mask[] = {
  0x00, 0x07, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1c, 0x00, 
  };

  const uint8_t * const Victims[] PROGMEM = { Victim_01, Victim_02, Victim_03, Victim_04, Victim_05, Victim_06, Victim_07, Victim_08 };
  const uint8_t * const Victims_Mask[] PROGMEM = { Victim_01_Mask, Victim_02_Mask, Victim_03_Mask, Victim_04_Mask, Victim_05_Mask, Victim_06_Mask, Victim_07_Mask, Victim_08_Mask };
  const uint8_t * const Victim_Halos[] PROGMEM = { Victim_Halo_01, Victim_Halo_02, Victim_Halo_03 };
  const uint8_t * const Victim_Halos_Mask[] PROGMEM = { Victim_Halo_01_Mask, Victim_Halo_02_Mask, Victim_Halo_03_Mask };

  const unsigned char PROGMEM Fireman_01[] = {
  40, 22,
  0x00, 0x70, 0x88, 0x14, 0x02, 0x16, 0x19, 0x61, 0x3a, 0x84, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x78, 0x04, 0x02, 0x0a, 0x22, 0x15, 0x62, 0xb2, 0x4c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x82, 0x45, 0x3e, 0x00, 0x80, 0x80, 0x11, 0x32, 0x24, 0x44, 0xc4, 0x38, 0xa8, 0xa8, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x38, 0x44, 0xc4, 0x04, 0x04, 0x03, 0x03, 0x00, 0x00, 0x00, 0x39, 0x27, 0x40, 0x60, 0x10, 0x10, 0xe0, 
  0x0c, 0x12, 0x13, 0x12, 0x10, 0x0f, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x09, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x24, 0x20, 0x22, 0x13, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 
  };

  const unsigned char PROGMEM Fireman_01_Mask[] = {
  0x00, 0x70, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xe4, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0x4c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x82, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0x38, 0xb8, 0xb8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x7c, 0xfc, 0x9c, 0xdc, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc0, 0xe0, 0xf0, 0xf0, 0xe0, 
  0x0c, 0x1e, 0x1f, 0x1f, 0x1f, 0x0f, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x3f, 0x3f, 0x3f, 0x1f, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 
  };

  const uint8_t * const Firemen[] PROGMEM = { Fireman_01 };
  const uint8_t * const Firemen_Mask[] PROGMEM = { Fireman_01_Mask };


}