##VLN56

This is our project for the course VLN1, we are group 56

The program is simply put a client for interacting with a database, the theme of this database are computer scientists.

#Commands

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

#Syntax

The add command can be used with a parameter to denote the name of the entry, or you can run the command interactively.

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

