This is a straightforward exercise and most of it was left unfinished.

The objective was to clean up the data by fixing typos, for example, there are many incorrect spellings of the movie title Avatar:The Last Airbender

To change all the instances without having to type out every variation of incorrect spelling we can use the following SQL command to fix all possible variations in one go:

UPDATE shows SET title = "Avatar:The Last Airbender" WHERE title LIKE "avatar%";

The rest can be done in similar fashion.
