/*
 * Copyright 2013 Henrik Baastrup
 *
 * Licensed under GNU Lesser General Public License, Version 3 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.gnu.org/licenses/lgpl-3.0.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GETTICKS_H
#define GETTICKS_H

typedef unsigned long long tick_type;

static inline tick_type
 get_ticks()
 {
#if defined(WIN32)

     LARGE_INTEGER data;
     __asm
     {
      // cpuid                        // why cpuid if we are interested in rdtsc? Nicola
         RDTSC       // Read Time-Stamp Counter into EDX:EAX
         MOV  data.u.LowPart,  EAX    // Store to C++ local variable (low 32 bit)
         MOV  data.u.HighPart, EDX    // Store to C++ local variable (high 32 bit)
     }
     return data.QuadPart;

#elif defined(__linux__)

#if defined(__i386__) // 32bit

     tick_type ret;
     __asm__ __volatile__("rdtsc" : "=A" (ret));
     return ret;

#elif defined(__x86_64__)  // 64bit

     unsigned int __a,__d;
     __asm__ __volatile__("rdtsc" : "=a" (__a), "=d" (__d));
     tick_type ret = ((unsigned long)__a) | (((unsigned long)__d)<<32);
     return ret;

#else
#error Unknow Linux arch type!
#endif
#elif defined(__APPLE__) && defined(__x86_64__)

     unsigned int __a,__d;
     __asm__ __volatile__("rdtsc" : "=a" (__a), "=d" (__d));
     tick_type ret = ((unsigned long)__a) | (((unsigned long)__d)<<32);
     return ret;

#else
#warning get_ticks: operating system not supported!
 return 0;
#endif

 }


#endif // GETTICKS_H
