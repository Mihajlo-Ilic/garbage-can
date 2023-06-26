# garbage-can
### Welcome to the trashlands!  
Garbage can is my hobby project to learn preprocessor  
meta programming in C++.  
> It's garbage can not garbage cannot!

![Example](showcase_images/second_example.png?raw=true "Current version")

Current features:

* Test syntax parsing
* Expect calls (comparing two arbitrary values)
* Assert calls (same as expect but exiting if it fails)

Need to be implemented:

* Grouping tests
  * Test Suite (Grouped tests that share a given resources)
  * Test Group (Grouped tests that have copies of given resources)
* Death tests (Forking a text and expecting a return from fork etc...)
* Disabling certain tests
* Benchmark tests (tests that are given certain time to finish)
* Output formats: xml,json,html  
  
* Mocking Data
* Mocking Calls
* Fuzzy mocking data (returning random data in range)