# 1st System Programming Assignment 2020
**D. Alexandres, 1115201400006.**  
First (1st) assignment on UNIX system programming,  
*University of Athens, 2020.*

#ENTOLH METAGLWTTISHS

Αρχικά ελέγχονται τα ορίσματα που έδωσε ο χρήστης στη γραμμή εντολών και γίνονται οι κατάλληλες αναθέσεις.
Διαβάζονται οι εγγραφές από το αρχείο εισόδου και ισχύουν όσα λέει η εκφώνηση.

Απορρίπτονται αρχεία που έχουν εγγραφές με λιγότερα ή περισσότερα από 7 (επτά) γνωρίσματα:
1.recordID, 2.patientFirstName, 3.patientLastName, 4.diseaseID, 5.country, 6.entryDate, 7.exitDate (που μπορεί ασφαλώς να είναι παύλα.)
Οποιαδήποτε εγγραφή δεν ακολουθεί αυτό το μοτίβο αγνοείται.

Όποιο και να είναι το bucketSize, δε γίνεται ο αριθμός κόμβων σε blocks να είναι 0. Θα είναι τουλάχιστον 1.

Στη /recordPatientExit:
  -ελέγχεται η ημερομηνία που δίνει ο χρήστης να είναι ορθή και επιπλέον δίνεται μήνυμα λάθους σε περίπτωση που δοθεί '-' γιατί θεωρώ πως αυτό δεν έχει λογική. Ο χρήστης που έχει βγει από νοσοκομείο δε θα ξαναμπεί με το ίδιο entrydate, χρειάζεται νέο record οπότε αυτό δεν είναι στις αρμοδιότητες του ερωτήματος αυτού.
  -εάν η εγγραφή με το δοθέν ID δεν υπάρχει, η εντολή αγνοείται με σχετικό μήνυμα λάθους.
  -εάν η δοθείσα ημερομηνία εξόδου είναι μικρότερη ή ιση της υπάρχουσας entry date, η εντολή αγνοείται με σχετικό μήνυμα λάθους
  -εάν ο ασθενής είχε ήδη κάποιο exit date, η εντολή αλλάζει αυτό το exitdate σε αυτό που έδωσε ο χρήστης τηρώντας φυσικά τους παραπάνω περιορισμούς.


ΕΞΩΤΕΡΙΚΕΣ ΑΝΑΦΟΡΕΣ
Για hash function : https://stackoverflow.com/questions/16075271/hashing-a-string-to-an-integer-in-c
tokenization of string : https://stackoverflow.com/questions/49201654/splitting-a-string-with-multiple-delimiters-in-c
