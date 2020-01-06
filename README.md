# Computer Systems Final Project

Program in C that pipes two terminal commands using pipe, fork, dup, and exec
## About

The program uses C primitives to imitate the following command on the linux terminal:
#### 
    cat sample.txt | grep 'word' 
The goal of this program is to function as a page search (like ctrl+f) on any text file. 

## Goals
I wanted to make a program that functioned as a search engine for talmudic abbreviations. Lists of explained abbreviations exist on [Wikipedia](https://en.wikipedia.org/wiki/List_of_Hebrew_abbreviations) but in order to find a given abbreviation, user would need to first navigate to the proper page, and sometimes multiple pages. This repo includes a basic python script that scrapes a page's abbreviation and can be saved as a text file for the c code to search. 
