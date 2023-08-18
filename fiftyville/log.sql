-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_
' AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.
-- New Info: Time is 10:15am, bakery name (Humprey Street bakery) is mentioned in witness' interviews
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript = '%Humprey Street bakery%';
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- New Info: Took earliest flight out of Fiftyville (destination) on 29 July.

-- In morning, atm at legget street, thief withdraw money

-- Within 10 minutes of the theft, I saw the thief get into a car in the bakery parking lot and drove away


-- New Info: Took earliest flight out of Fiftyville (destination) on 29 July.
SELECT id FROM airports
    WHERE city = 'Fiftyville';
-- New Info: The origin airport's id: 8
SELECT destination_airport_id, hour, minute FROM flights
    WHERE month = 7 AND day = 29 AND origin_airport_id = 8
    ORDER BY hour, minute;
-- New Info: destination_airport_id = 4. plane took off at 0820
SELECT city FROM airports
    WHERE id = 4;
-- Destination airport, city: LaGuardia Airport, New York City
SELECT id FROM flights
    WHERE origin_airport_id = 8 AND destination_airport_id = 4 AND month = 7 AND day = 29;
-- New Info: flight_id: 36
SELECT year FROM flights
    WHERE id = 36;
-- New Info: year is 2021
SELECT passport_number FROM passengers
    WHERE flight_id = 36;
-- New Info: Possible theft passport_id are: 7214083635, 1695452385, 5773159633, 1540955065, 8294398571, 1988161715, 9878712108, 8496433585
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- New Info: Obtained a list of 8 names

-- Kenny, Sofia, Taylor, Luca, Kelsey, Edward, Bruce, Doris


-- Within 10 minutes of the theft, I saw the thief get into a car in the bakery parking lot and drove away
SELECT name FROM people where license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 and minute <= 25 and minute >= 15 and activity = 'exit');

-- Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce

-- Overlap
-- Luca, Sofia, Bruce, Kelsey

-- they called someone who talked to them for less than a minute.
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);

-- Overlap
-- Bruce, Kelsey, Sofia

-- Atm
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

--overlap: Bruce

-- New Info: Obtained a list of license plates
SELECT name FROM people WHERE passport_number iN(SELECT passport_number FROM passengers WHERE flight_id = 36);
    INTERSECT
SELECT name, phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit');
-- Obtained a list of 5 names
SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Obtained a list of around 10 phone calls
SELECT name FROM people
    WHERE passport_number iN
    (SELECT passport_number FROM passengers
    WHERE flight_id = 36)
INTERSECT
SELECT name FROM people
    WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit')
INTERSECT
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- New Info: obtained a list of 4 names: Bruce, Kelsey, Sofia, Taylor
SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND
-- New Info: receiver's phone number is (367) 555-5533, (499) 555-9472, (389) 555-5198, (130) 555-0289, (286) 555-6063
SELECT name, phone_number FROM people
    WHERE passport_number iN
    (SELECT passport_number FROM passengers
    WHERE flight_id = 36)
INTERSECT
SELECT name, phone_number FROM people
    WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit' AND hour = 10 AND minute <= 25 AND minute >= 15)
INTERSECT
SELECT name, phone_number FROM people
    WHERE phone_number IN
    (SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
--
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- New Info: about 10 account numbers
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller in (SELECT phone_number FROM people WHERE name = 'Bruce'));                                                                                                                  ;
