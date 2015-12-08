#VLN56

This is our project for the course VLN1, we are group 56!

This program, simply put, is a client for interacting with a database. The theme of this database are computer scientists and computers.

##Commands

The following commands are currently implemented into the program

| Command       | Description                                | Sortability                                                                        |
| ------------- |:------------------------------------------:|------------------------------------------------------------------------------------|
| add           | Adds a new entry to the database           | Does not apply                                                                     |
| search        | Searches the database                      | Ascending/Descending by any field (except Description field, does not apply there) |
| list   | Displays all entries found in the database | Ascending/Descending by any field (except Description field, does not apply there) |
| remove  | Remove an entry in the database | Does not apply |
| connections | View specific connections| Ascending/Descending by any field (except Description field, does not apply there) |
| exit | Close the program | Does not apply |
| help          | Displays all commands                      | Does not apply                                                                     |

Please keep in mind that the program sorts it's data case sensitively. i.e. given the data set Bob, jack, Susan, susan; it will be sorted Bob, Susan, jack, susan or susan, jack, Susan, Bob.

Commands are not case sensitive unless they are used with parameters. For example ADD Jack Sparrow does not work, but ADD works.

##Syntax
Throughout this section a COLUMN_ID will be referenced.  To better understand what COLUMN_ID is, please refer to the table below: 

For Persons:

|   ID     |   Data      |
| -------- | ----------- |
| 1        | Name        |
| 2        | Birthyear   |
| 3        | Deathyear   |
| 4        | Sex         | 
| 5        | Profession  |

For Computers:

|   ID   |         Data      |
|------- | ----------------- |
|   1    | Name              |
|   2    | Construction year |
|   3    | Type              |
|   4    | Built             |



###add
The add command can be used with a parameter to denote the name of the entry, or you can run the command interactively. 
The user is not able to write digits or special characters (like the icelandic letters þ, í, æ) in the name of the person. 
The only field allowed to be empty is the description field.
The death year cannot be prior to the birth year. But there are no other constrains for the years except they cannot be < 0, i.e. it is allowed to fill in birth year and death year that have not passed. If the person is still alive, the programs asks the user to put in 0 as death year and prints out NA when printing out results.


Syntax:
```
add
```
Example

adding a computer scientist
```
> add
Do you want to add a Computer Scientists, Computer or connection between Computer Scientist and a Computer?
(1) Computer Scientist
(2) Computer
(3) Connection between Computer Scientist and a Computer
> 1
You will be asked to enter information about the person.
Please write the name of the person: 
> Leia Organa
Please write the profession of the person: 
> Princess
Please write a description of the person, can be left blank if you desire: 
> 
Please write the year that the person was born: 
> 32
Please write the year that the person died, if the person is still alive enter 0: 
> 0
Enter the sex of the person: 
(m) Male
(f) Female
(o) Other
> f

```
or
 
adding a computer
```
> add
Do you want to add a Computer Scientists, Computer or connection between Computer Scientist and a Computer?
(1) Computer Scientist
(2) Computer
(3) Connection between Computer Scientist and a Computer
> 2
You will be asked to enter information about the computer.
Please enter the name of the computer: 
> Nintendo
Please enter the construction year of the computer: 
> 1980
Please enter the type of the computer: 
> Electronic
Was the computer built?
0 for No 
1 for Yes 
> 1
Please write some description of the computer, can be left blank if desired: 
> Super Mario Brothers is the best ever!
```
or

adding a connection
```
> add
Do you want to add a Computer Scientists, Computer or connection between Computer Scientist and a Computer?
(1) Computer Scientist
(2) Computer
(3) Connection between Computer Scientist and a Computer
> 3
Below is a list of all Scientist in the database, please choose the id of the Scientist you want to connect to a computer.
> Id: 1	Name: Ada Lovelace
Id: 2	Name: Grace Hopper
Id: 3	Name: Anita Borg
Id: 4	Name: Shafi Goldwasser 
Id: 5	Name: Frances E. Allen 
Id: 6	Name: Erna Schneider 
Id: 7	Name: Charles Babbage 
Id: 8	Name: Alan Turing 
Id: 9	Name: Linus Torvalds
Id: 10	Name: Edsger W. Dijkstra 
Id: 11	Name: Jon Von Neuman 
Id: 12	Name: Claude Shannon
Id: 13	Name: Donald Knuth
> 2
Below is a list of all Computer in the database, please choose the id of the Computer you want to connect to the previously chosen Scientist.
> Id: 1	Name: Difference Engine
Id: 2	Name: Analytical Engine
Id: 3	Name: Eniac
Id: 4	Name: Apple I
Id: 5	Name: Harvard Mark I
Id: 6	Name: The Turing Machine
Id: 7	Name: Z1
Id: 8	Name: Transistor computer
Id: 9	Name: Apple II
Id: 10	Name: Nintendo
> 10
```
In the last example, Grace Hopper was connected to Nintendo.

###search
The search command can be used to search for entries in the database. When searching the user needs to specify in what column he wants to search. Results for computer scientists can be sorted by name, birth year, death year, sex or profession and for computers they can be sorted by name, construction year, type or year built. This command is not case sensitive.

Syntax:
```
search
search Table
search Table   COLUMN_ID
search Table   COLUMN_ID   COLUMN_ID SUBSTRING
```

Example

```
search
Do you want to search in the database of Computer Scientists or Computers?
(1) Computer Scientists
(2) Computers
> 2
Choose what information you want to search for:
(1) Name
(2) Construction Year
(3) Type
(4) Built
(5) Description
> 3
What substring do you want to search for?
> Mechanical
What do you want to sort by? choose one of the following:
(1) Name
(2) Construction Year
(3) Type
(4) Built
> 2
Do you want the information sorted in ascending or descending order? choose a/d
> a
```
or
```
> search 1 6 American
Do you want to search in the database of Computer Scientists or Computers?
(1) Computer Scientists
(2) Computers
> Choose what information you want to search for:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
(6) Description
> What substring do you want to search for?
> What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
> 1
Do you want the information sorted in ascending or descending order? choose a/d
> a
```


The first example should display all entries that include "Mechanical" in the description field sorted alphabetically by name in ascending order. 
The second example should display all entries that include "American" in the description field sorted alphabetically by name in ascending order.

###list
The list command can be used to list all entries in the database. The results can be sorted as previously stated.

Syntax:
```
list
list COLUMN_ID ORDER
```


Example

```
> list
```
displays all entries sorted alphabetically by name in ascending order.

```
> list
Do you want a list of Computer Scientists, Computers or connections between Computer Scientist and a Computer?
(1) Computer Scientists
(2) Computers
(3) Connection between Computer Scientists and Computers

> 1

What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession

> 1

Do you want the information sorted in ascending or descending order? Choose a/d

> a

```
###remove
This command can be used to remove a computer scientist, a computer or a connection.

Example
```
> remove
Do you want to remove a Computer Scientist, a Computer or a connection between a Computer Scientist and a Computer?
(1) Computer Scientist
(2) Computer
(3) Connection between a Computer Scientist and a Computer
> 1
Below is a list of all Computer Scientists in the database, please enter the Id of the Scientist you want to remove: 
> Id: 1	Name: Ada Lovelace
Id: 2	Name: Grace Hopper
Id: 3	Name: Anita Borg
Id: 4	Name: Shafi Goldwasser 
Id: 5	Name: Frances E. Allen 
Id: 6	Name: Erna Schneider 
Id: 7	Name: Charles Babbage 
Id: 8	Name: Alan Turing 
Id: 9	Name: Linus Torvalds
Id: 10	Name: Edsger W. Dijkstra 
Id: 11	Name: Jon Von Neuman 
Id: 12	Name: Claude Shannon
Id: 13	Name: Donald Knuth
Id: 15	Name: Leia Organa
> 15
```
This example shows how the user can remove Leia Organa from the list.


###connection
This command is found under the list command and can be used to see the connection between a computer scientist/computer and a computer/computer scientist.

Example

```
> list
Do you want a list of Computer Scientists, Computers or connections between Computer Scientist and a Computer?
(1) Computer Scientists
(2) Computers
(3) Connection between Computer Scientists and Computers
> 3
	   Persons 				                     Computers
Id: 1	Name: Ada Lovelace		    Id: 1	Name: Difference Engine
Id: 8	Name: Alan Turing 		    Id: 6	Name: The Turing Machine
Id: 7	Name: Charles Babbage 		Id: 1	Name: Difference Engine
Id: 7	Name: Charles Babbage 		Id: 2	Name: Analytical Engine
Id: 2	Name: Grace Hopper		    Id: 5	Name: Harvard Mark I
Id: 11	Name: Jon Von Neuman 		Id: 5	Name: Harvard Mark I
Id: 11	Name: Jon Von Neuman 		Id: 3	Name: Eniac

```
###help
This command prints out a list of commands

Syntax:
```
> help

-------------------------------------------------
add: Add to the database
search: Search the list for preferred information
list: Display the whole list in preferred order
remove: Remove an entry in the database
connections: View specific connections
exit: Close the program
help: Displays this screen
-------------------------------------------------


```



###exit
This command exits the program

Syntax:
```
> exit
```
