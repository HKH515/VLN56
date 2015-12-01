#VLN56

This is our project for the course VLN1, we are group 56

The program is simply put a client for interacting with a database, the theme of this database are computer scientists.

##Commands

the following commands are currently implement into the program

| Command       | Description                                | Sortability                                                                        |
| ------------- |:------------------------------------------:|------------------------------------------------------------------------------------|
| list          | displays all entries found in the database | Ascending/Descending by any field (except Description field, does not apply there) |
| add           | adds a new entry to the database           | Does not apply                                                                     |
| search        | searches the database                      | Ascending/Descending by any field (except Description field, does not apply there) |
| help          | displays all commands                      | Does not apply                                                                     |

please keep in mind that the program sorts it's data case sensitively. i.e. given the data set Bob, jack, Susan, susan; it will be sorted Bob, Susan, jack, susan or susan, jack, Susan, Bob.

When the list is sorted after something other than Name, it is though internally ordered after Name.
Commands are case sensitive, ADD, Add and aDD do not work, only add.
It is not allowed to write digits or special characters (like the icelandic letters þ, í, æ) in the name of the person.

##Syntax
Throughout this section a COLUMN_ID will be referenced, to make sense of this please take a look at the table below

How the columns are set up

|   ID     |   Data      |
| -------- | ----------- |
| 1        | Name        |
| 2        | Birthyear   |
| 3        | Deathyear   |
| 4        | Sex         |
| 5        | Profession  |



###add
The add command can be used with a parameter to denote the name of the entry, or you can run the command interactively.

Syntax:
```
add NAME
add
```
Example

```
>add John Appleseed
You will be asked to enter information about the person
Please write the name of the person:
Please write the profession of the person:
>Software Tester
Please write some description of the person:
>This is a very detailed description.
Please write the year the person was born:
>1984
Please write the year the person died, if the person is still alive enter 0:
>2011
Enter the sex of the person
(m) Male
(f) Female
(o) Other
>m
```
or

```
add
You will be asked to enter information about the person
Please write the name of the person:
>John Appleseed
Please write the profession of the person:
>Software Tester
Please write some description of the person:
>This is a very detailed description.
Please write the year the person was born:
>1984
Please write the year the person died, if the person is still alive enter 0:
>2011
Enter the sex of the person
(m) Male
(f) Female
(o) Other
>m
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
>list 1 a
```
would display all entries sorted alphabetically by name in ascending order.

```
>list
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
1
Do you want the information sorted in ascending or descending order? choose a/d
a
```
###search
The list command can be used to list all entries in the database, it can also display data sorted by name, birth year, death year or sex.

Syntax:
```
search
search COLUMN_ID
search COLUMN_ID SUBSTRING
```

Example

```
>search 3 American
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
>1
Do you want the information sorted in ascending or descending order? choose a/d
>a
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
>3
What substring do you want to search for?
American
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
>1
Do you want the information sorted in ascending or descending order? choose a/d
>a
search
Choose what information you want to search for:
(1) Name
(2) Profession
(3) Description
(4) Birthyear
(5) Deathyear
(6) Sex
>3
What substring do you want to search for?
>American
What do you want to sort by? choose one of the following:
(1) Name
(2) Birthyear
(3) Deathyear
(4) Sex
(5) Profession
1
Do you want the information sorted in ascending or descending order? choose a/d
>a

```
both of these examples should display all entries that include an "American" in the description field sorted alphabetically by name in ascending order.

###help
This command prints out a list of commands

Syntax:
```
>help

-------------------------------------------------
add: Add to the database
search: Search the list for prefered information
list: Display the whole list in prefered order
exit: Close the program
help: Displays this screen
-------------------------------------------------


```



###exit
This command exits the program

Syntax:
```
>exit
```
