-- Keep a log of any SQL queries you execute as you solve the mystery.

# This is the output of the querie for the description of the crime reports for the year 2023 month 7 and day 28 on Humphrey Street
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

Littering took place at 16:36. No known witnesses.

# This is the output of the querie for the interviews of the three witnesses that were interviewed after the crime
SELECT transcript, name FROM interviews WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> transcript LIKE "%bakery%";
1. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.|Ruth
2. I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.|Eugene
3. As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.|Raymond

Relevant information taken from this querie is to check the bakery_security_logs for a car that left the bakery 10 minutes after the crime. Another possible lead
is that the thief used an ATM on Leggett Street the morning of the crime. And the final lead is that the thief talked to another person after the crime asking the person
to purchase a flight ticket for the earliest flight possible the following day, July 29,2021. The call lasted for less than a minute.





# This is the output of the querie for the phone calls that happend the day of the crime that had a duration of less than 60 seconds
SELECT * FROM phone_calls WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> duration < 60;
221|(130) 555-0289|(996) 555-8899|2021|7|28|51
224|(499) 555-9472|(892) 555-8872|2021|7|28|36
233|(367) 555-5533|(375) 555-8161|2021|7|28|45
251|(499) 555-9472|(717) 555-1342|2021|7|28|50
254|(286) 555-6063|(676) 555-6554|2021|7|28|43
255|(770) 555-1861|(725) 555-3243|2021|7|28|49
261|(031) 555-6622|(910) 555-3251|2021|7|28|38
279|(826) 555-1652|(066) 555-9701|2021|7|28|55
281|(338) 555-6650|(704) 555-2131|2021|7|28|54

# This is the output of the querie for the ATM activity on the day of the crime
SELECT * FROM atm_transactions WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> atm_location = 'Leggett Street';
246|28500762|2021|7|28|Leggett Street|withdraw|48
264|28296815|2021|7|28|Leggett Street|withdraw|20
266|76054385|2021|7|28|Leggett Street|withdraw|60
267|49610011|2021|7|28|Leggett Street|withdraw|50
269|16153065|2021|7|28|Leggett Street|withdraw|80
275|86363979|2021|7|28|Leggett Street|deposit|10
288|25506511|2021|7|28|Leggett Street|withdraw|20
313|81061156|2021|7|28|Leggett Street|withdraw|30
336|26013199|2021|7|28|Leggett Street|withdraw|35

# To get a first list of suspects I will find the name of the people who match with these bank accounts
SELECT person_id FROM bank_accounts WHERE account_number IN
   ...> (SELECT account_number FROM atm_transactions WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> atm_location = 'Leggett Street');
686048
948985
514354
458378
395717
396669
467400
449774
438727

So these are the person ids of the owners of the bank accounts that were used at the ATM on Leggett Street on the day of the crime

Now to find the names of the owners of the accounts using their person ids on the people table

SELECT name FROM people WHERE id IN
   ...> (SELECT person_id FROM bank_accounts WHERE account_number IN
   ...> (SELECT account_number FROM atm_transactions WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> atm_location = 'Leggett Street'));
Kenny
Iman
Benista
Taylor
Brooke
Luca
Diana
Bruce
Kaelyn

Now with this initial list of suspects we can find the phone number of the person to check whether they made a phone call on the day of the
crime that lasted less than a minute or whether through their license plate they were at the scene of the crime.

# This is the output of the querie for the phone call ids of phone calls made by one of the suspects on the day of the crime

sqlite> SELECT id FROM phone_calls WHERE caller IN
   ...> (SELECT phone_number FROM people WHERE id IN
   ...> (SELECT person_id FROM bank_accounts WHERE account_number IN
   ...> (SELECT account_number FROM atm_transactions WHERE
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> atm_location = 'Leggett Street')))
   ...> AND duration < 60 AND
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28;
233
254
255
279
281

Now to dwindle down the list of suspects with this
sqlite> SELECT name FROM people WHERE id IN
   ...> (SELECT id FROM people WHERE phone_number IN
   ...> (SELECT caller FROM phone_calls WHERE id IN (233, 254, 255, 279, 281)));
Kenny
Benista
Taylor
Diana
Bruce

Now to see who they called on the day of the crime
sqlite> SELECT name FROM people WHERE id IN
   ...> (SELECT id FROM people WHERE phone_number IN
   ...> (SELECT receiver FROM phone_calls WHERE id IN (233, 254, 255, 279, 281)));
James
Anna
Philip
Robin
Doris

These are the people that received a call on the day of the crime.

Now to see if any of our suspects were at the bakery they day of the crime
sqlite> SELECT id, activity, license_plate FROM bakery_security_logs WHERE license_plate IN
   ...> (SELECT license_plate FROM people WHERE name IN ('Kenny', 'Benista', 'Taylor', 'Diana', 'Bruce')) AND
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28;
232|entrance|94KL13X
237|entrance|1106N58
240|entrance|322W7JE
261|exit|94KL13X
266|exit|322W7JE
268|exit|1106N58

So lets narrow down the list of suspects again with this information
sqlite> SELECT name FROM people WHERE license_plate IN ('94KL13X', '1106N58', '322W7JE');
Taylor
Diana
Bruce

These are the flight ids of the flights with origin airport Fiftyville that took place the following day after the crime
SELECT id FROM flights WHERE origin_airport_id = 8 AND
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 29;
18
23
36
43
53

The earliest of these flights is the one with flight id = 36

Lets see who was on this flight
sqlite> SELECT name FROM people WHERE name IN ('Taylor', 'Diana', 'Bruce') AND passport_number IN
   ...> (SELECT passport_number FROM passengers WHERE flight_id = 36);
Taylor
Bruce

So now we only have two suspects, Taylor and Bruce

Now to check what time they were at the bakery the day of the crime
SELECT hour, minute, license_plate FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE name IN ('Taylor', 'Bruce'));
8|23|94KL13X
8|34|1106N58
10|18|94KL13X
10|35|1106N58

They were both at the bakery around the time of the crime but I suspect it was the owner of license plate 94KL13X since it left 3 minutes after the crime.
The owner of that license plate is
sqlite> SELECT name FROM people WHERE license_plate = '94KL13X';
Bruce

Now to find the acomplice he called after the crime
qlite> SELECT name FROM people WHERE phone_number IN
   ...> (SELECT receiver FROM phone_calls WHERE caller IN
   ...> (SELECT phone_number FROM people WHERE name = 'Bruce') AND
   ...> year = 2021 AND
   ...> month = 7 AND
   ...> day = 28 AND
   ...> duration < 60);
Robin

So the thief is Bruce and his acomplice is Robin and the destination of his flight was
sqlite> SELECT city FROM airports WHERE id IN
   ...> (SELECT destination_airport_id FROM flights WHERE id = 36);
New York City

