It is a mini routing system in which the program will read the network.csv file and then make a network and calculate routing tables of all routers using dijkstra algorithm.
It has the following commands:
1. send_msg will take messageId:priority:source:destination:payload.
  It will calculate the shortest path using the destination's parent and destination's parent's parent and so on. And when it reaches the router then It will send message the next destination.
2. send_msgs will take txt file name which has multiple messages with same format as in 1. hello.txt and hello1.txt are made for this purpose.
3. print_path will take 3 arguments which can be * to show for all or specific destinations separated by to keyword. But it will not take both *s
4. change_edge will take 3 arguments separated by colon (:). These are source:destination:weight. It created the path with the given weight between source and destination. It will then recalculate the routing tables usign dijkstra.
5. change_edges will take 1 argument which is the network file name which must be in correct format as of the default network.csv and network2.csv.
  network2.csv is created to test change_edges command.
