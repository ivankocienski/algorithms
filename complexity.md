# Complexity

Software engineering is about developing a solution to a problem. As engineers we need to understand the requirements asked of the software and the costs of implementing said software. Any choice made represents a balance of trade-offs that are reflected by the software and how it performs.

At the heart of every piece of software is a set of algorithms that actually perform the desired behaviour. By developing an understanding of these algorithms (in their simplest terms) we can make better informed decisions.

Asymptotic Complexity Analysis is about this study of algorithms and how they execute in various conditions. This done turning the algorithm into a function that takes as its input the size of data. For example an algorithm that returns the length of a string S will have a function that takes the length of S as the number N- so N is the length of S.


## Big O

Big O analysis looks at the total resource usage (time or memory) as a function of the maximum amount of work done for a given size of input N. It is written as O(N) and represents the upper bounds of the algorithm. As N gets larger the O(N) can increase as well.

The best algorithm has an O(1) meaning for any size of N this operation will only have one step. An example of this would be an array access where only one value is retrieved from a fixed in-memory array.

The next best class of algorithms is O(N) where for a given size an exact number of steps of size N is taken. An example of this would be counting the number of values in an array that matches a given input.

Algorithms that scale poorly fit into the class of O(N^2) or O(2^N) or worst O(N!). As the size of N grows the amount of work is compounded. An example would be an algorithm that cross-references two arrays (of the same size) where for each element in A a scan of B must be performed.

More optimal algorithms fit into the class of O(log(N)) or O(N*log(N)) where as the input size grows the amount of work grows logarithmicly. An example of this type of algorithm is the 'divide-and-concur' type where each iteration splits the input in 2 and then operates on the two smaller pieces, repeating until the partition can no longer be made.

## Big &omega; (Omega)

Big &omega; represents the best case of performance; in a sorting algorithm how much work is performed if the input is already sorted?

An algorithm that finds a value in an array has a &omega;(1) because in the best case scenario the value being sought will be at the start.

## Big &theta; (Theta)

Big theta takes the average of Big O and Big &omega; giving an aproximate expense for a given input.

## Making the choice

Unfortunately there is usually no simple choice when selecting an algorithm. A number of factors must be considered such as:

- *How big is the data?* Picking a highly tuned algorithm for a dataset of a few thousand records or less may be uneccassery. 
- *How frequently will the data arrive?* If the algorithm is only being run once a day or less then a few hours may not impact performance of the greater application.
- *Is the data being used in real time?* Unlike the previous point an algorithm that is expected to produce a result immediatly may wish to put constraints on the data input to ensure throughput.
- *Does the data change size?* If only a fixed size (or a size that has an upper limit) of data is being processed can the algorithm be set up to re-use memory resources or a look up table?
- *Does the data have order?* If the data is highly ordered (such as XML or JSON) then extracting information will be quicker than a informal format (like a text file).
- *Is the data going to be read or written to?* If you are mainly reading data from a fixed table in memory then lookup could be made faster (by using an index) at the cost of insertion cost. But if the usage profile involves heavy writing then that should be optimised at the cost of fast read access.
- *Can the data be pre-filtered?* If the algorithm chosen is very expensive for certain data can these data be removed before processing?
- *What is the cost of failure?* If a "fast but loose" algorithm is used and ocasionally produces bad outputs, what are the costs? A bank transaction is something that should be secure, dependable and repeatable but "view counter" on a website does not need to be as precise.
- *Where is the bottleneck?* If you are tuning an algorithm to save a few miliseconds in response time when the back-end is talking to a slow disk based database, does the algorithm need to be faster?

Even with these considerations there will be unforeseen circumstances that will arise from real world usage. It is best to utilise telemetry around the algorithm to gather evidence to make a better informed choice.

