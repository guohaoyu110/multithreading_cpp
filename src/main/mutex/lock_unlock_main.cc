#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

#include "src/lib/utility.h"

// A demo for lock and unlock of mutexes

// Run this using one of the following methods:
//  1. With bazel: bazel run src/main/mutex:{THIS_FILE_NAME_WITHOUT_EXTENSION}
//  2. With plain g++: g++ -std=c++17 -lpthread
//  src/main/mutex/{THIS_FILE_NAME}  -I ./
std::mutex g_mutex;
unsigned long g_counter;

void Incrementer() {
  for (size_t i = 0; i < 100; i++) {
    g_mutex.lock();
    g_counter++;
    g_mutex.unlock();
  }
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 100; i++) {
    threads.push_back(std::thread(Incrementer));
  }

  for (std::thread &t : threads) {
    t.join();
  }
  std::cout << "g_counter: " << g_counter << std::endl;

  assert(g_counter == 100 * 100);
}