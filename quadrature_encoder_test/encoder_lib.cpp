void _ISR_A() {
  //Serial.println("ISRA");
}

void _ISR_B() {
  //Serial.println("ISRB");
}

// // look for a low-to-high on channel A
// if (digitalRead(encoder0PinA) == HIGH) { 
//
//   // check channel B to see which way encoder is turning
//   if (digitalRead(encoder0PinB) == LOW) {  
//     encoder0Pos = encoder0Pos + 1;         // CW
//   } 
//   else {
//     encoder0Pos = encoder0Pos - 1;         // CCW
//   }
// }
//
// else   // must be a high-to-low edge on channel A                                       
// { 
//   // check channel B to see which way encoder is turning  
//   if (digitalRead(encoder0PinB) == HIGH) {   
//     encoder0Pos = encoder0Pos + 1;          // CW
//   } 
//   else {
//     encoder0Pos = encoder0Pos - 1;          // CCW
//   }
// }
// Serial.println (encoder0Pos, DEC);          
// // use for debugging - remember to comment out
//
//}
//
//void doEncoderB(){
//
// // look for a low-to-high on channel B
// if (digitalRead(encoder0PinB) == HIGH) {   
//
//  // check channel A to see which way encoder is turning
//   if (digitalRead(encoder0PinA) == HIGH) {  
//     encoder0Pos = encoder0Pos + 1;         // CW
//   } 
//   else {
//     encoder0Pos = encoder0Pos - 1;         // CCW
//   }
// }
//
// // Look for a high-to-low on channel B
//
// else { 
//   // check channel B to see which way encoder is turning  
//   if (digitalRead(encoder0PinA) == LOW) {   
//     encoder0Pos = encoder0Pos + 1;          // CW
//   } 
//   else {
//     encoder0Pos = encoder0Pos - 1;          // CCW
//   }
// }
//
//} 

