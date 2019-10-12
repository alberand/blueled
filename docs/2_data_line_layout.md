Author: Andrey Albershteyn
Date: 28.07.19
Status: Good Enough [Thrown away/Good Enough/Fully Solved]
Tags: hardware, layout

### Brief 

How to layout data line to the led strip? It is quite fast

### Timeline - Analysis & Solution

**[12.10.19]**

According to [this answer][1] the speed at which my device is operating is so
slow that it shouldn't be an issue for me. There are two main points to
consider:

* Signal integrity
* EMC

EMC can be caused by bad layout. 

* The shorter the line is the better. 
* Less vias better
* No sharp bends
[There][2] are a few good points on lay outing data lines

Signal integrity should be a problem in my case as it depends on slew/fall rate
which is quite slow in my case. 

There is no crosstalk in my case.


### References:

[1]: https://electronics.stackexchange.com/questions/9819/how-should-i-route-spi-lines
[2]: https://www.cypress.com/file/196526/download
