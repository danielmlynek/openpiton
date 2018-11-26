// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.
//
// Author: Michael Schaffner <schaffner@iis.ee.ethz.ch>, ETH Zurich
// Date: 26.11.2018
// Description: Simple hello world program that prints the core id. Also runs correctly on
// SMP system.
//

#include "ariane_common.h"

// global synchronization variable
volatile int amo_cnt=0;
const    int one=1;

// this is a simple test program that just prints
// hello world 32 times to the UART
int main(int argc, void ** argv) {

  char coreMsg[] = "Hello world, this is hart   !\n";

  // synchronize with other cores and wait until it is this core's turn
  while(amo_cnt != argc);

  // assemble number and print
  num2str(coreMsg, argc, 27, 2);
  printStr(coreMsg);

  // increment amo counter
  __asm__ __volatile__ (  " amoadd.d zero, %1, %0" : "+A" (amo_cnt) : "r" (one) : "memory");

  // hit pass trap and exit
  pass();
  return 0;
}