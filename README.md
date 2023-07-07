# the-trip-
modelling a trip booking program
This project is a trip booking system that incorporated various features and 
functionalities. It follows an object-oriented programming approach and 
utilizes concepts such as classes, graphs, searching, sorting, hash-map, STL,
loops, vectors, string, conditional statements and SDL library.

There is an internal initialisation of the graph nodes as an analogy to the 
different locations. Edges (with weights) are considered as routes between 
places. The information regarding all drivers is fed internally.

This program allows user to generate their account (sign-up) or to use the 
existing account (login). Their mail id is considered to be unique, does not 
allow users to use already registered email or password. Password can be 
changed if user forgets his/her password by just entering their correct mail id. 
Wrong details do not allow user to enter the program for vehicle booking.

Once user have successfully created their account or have login, program 
prompts options to book vehicle. User is asked to enter their current location
(pick-up) and their destination. Then program prompts the list of drivers and 
their information (rating, cost of travel, time of travel, name, contact number
and other details). User can select any of the driver as per their rating or cost or 
time to reach etc. Dijkstra algorithm is used to find the optimal path as well 
the shortest distances of journey.

Program prompts user to continue or cancel booking, also narrates the 
payment methods. If user books the vehicle, program tracks the current 
position of the booked vehicle, pick-up location, destination and the path that 
the vehicle has chosen all are highlighted and presented on screen of user (so 
the user can keep a track of their journey). Presentation of the map and all
other features is done by using SDL window with an appropriate delay time for 
screen.

Finally, the system prompts user to provide feedback and reviews (rating)
about the service offered.
