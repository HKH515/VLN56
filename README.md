#VLN56

This is our project for the course VLN1, we are group 56!

This program, simply put, is a client for interacting with a database. The theme of this database are computer scientists and computers.

##
![test image] (https://github.com/HKH515/VLN56/blob/85f3ea3e2189482629c1c217b79258ab7072c479/Images/Screen%20Shot%202015-12-14%20at%2011.28.12%20AM%20copy.jpg?raw=true)

In this window the user is able to learn about the fascinating world of computer science by choosing Computer Scientists, Computers or Connections between the two, in the dropdown box located at the top left side.
The sorting can be changed from ascending to descending by clicking on the Name, Birth Year, Death Year or Sex tab. Note that only one sorting option is available at a time. In this example the list is sorted by Name and in ascending order, where Ada Lovelace is first. 

##Syntax
Throughout this section a COLUMN_ID will be referenced.  To better understand what COLUMN_ID is, please refer to the table below: 

|   ID     |   Data      |
| -------- | ----------- |
| 1        | Name        |
| 2        | Birthyear   |
| 3        | Deathyear   |
| 4        | Sex         |
| 5        | Profession  |



###add
The add command can be used with a parameter to denote the name of the entry, or you can run the command interactively. 
The user is not able to write digits or special characters (like the icelandic letters þ, í, æ) in the name of the person. 
The only field allowed to be empty is the description field.
The death year cannot be prior to the birth year. But there are no other constrains for the years except they cannot be < 0, i.e. it is allowed to fill in birth year and death year that have not passed. If the person is still alive, the programs asks the user to put in 0 as death year and prints out NA when printing out results.


Syntax:
```
add NAME
add
```
Example

```
> add John Appleseed
You will be asked to enter information about the person
Please write the name of the person:
Please write the profession of the person:
> Software Tester
Please write a description of the person:
> This may be a very detailed description.
Please write the year that the person was born:
> 1984
Please write the year that the person died, if the person is still alive enter 0:
> 2011
Enter the sex of the person:
(m) Male
(f) Female
(o) Other
> m
```
or

```
add
You will be asked to enter information about the person
Please write the name of the person:
> John Appleseed
Please write the profession of the person:
> Software Tester
Please write a description of the person:
> This is a very detailed description.
Please write the year that the person was born:
> 1984
Please write the year that the person died, if the person is still alive enter 0:
> 2011
Enter the sex of the person:
(m) Male
(f) Female
(o) Other
> m
```

###list
The list command can be used to list all entries in the database, it can also display data sorted by name, birth year, death year or sex.

Syntax:
```
list
list COLUMN_ID ORDER
```


Example

```
> list 1 a
```
would display all entries sorted alphabetically by name in ascending order.

```
> list
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
> 1
Do you want the information sorted in ascending or descending order? choose a/d
> a
```
###search
The search command can be used to search for entries in the database. When searching the user needs to specify in what column he wants to search. Results can be sorted by name, birth year, death year or sex.

Syntax:
```
search
search COLUMN_ID
search COLUMN_ID SUBSTRING
```

Example

```
> search 3 American
Choose what information you want to search for:
(1) Name
(2) Profession
(3) Description
(4) Birthyear
(5) Deathyear
(6) Sex
What substring do you want to search for?
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
> 1
Do you want the information sorted in ascending or descending order? choose a/d
> a
```

```
search
Choose what information you want to search for:
(1) Name
(2) Profession
(3) Description
(4) Birthyear
(5) Deathyear
(6) Sex
> 3
What substring do you want to search for?
American
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
> 1
Do you want the information sorted in ascending or descending order? choose a/d
> a
```
Both of these examples should display all entries that include an "American" in the description field sorted alphabetically by name in ascending order.

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
