Logic-tron (Honors group project for CSCE 121)
==============================================

**C++11/FLTK graphical editor and simulator for combinatorial logic circuits.**

*Cassie Bub, Jake Leland, Humberto Munoz-Bauza*


Must Do
-------
* Reading from and writing to a file
* Draw dots to indicate junctions where wires are supposed to be connecting (I can take care of this - Jake)
* Verify that we have used at lease two C++11 features (such as auto and range-based for)
* Verify that each function is limited to no more than 24 lines

Possible Improvements
---------------------
* Somehow indicate to the user which inputs they have selected to construct the gate
* Shrink the size of the gates so that they don't fill the entire space between lines
* Prevent the user from adding any more gates once they run out of space in the window

Extra Credit
------------
* Allow the user to change the most recent gate type and inputs until an "Accept" button is clicked. Every time the gate or its inputs are changed, update the truth table.
* Allow the user to input a desired truth table and then show whether the most recent gate added has that truth table <-- this one should be easy
