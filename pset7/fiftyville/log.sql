-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime scene report. Only checking for street to see a sample of the output data
SELECT * FROM crime_scene_reports
WHERE street LIKE "Humphrey %";

-- Check interviews of the 3 witnesses from that date that mention bakery
SELECT name, transcript FROM interviews
WHERE month = 7 AND day = 28
AND year = 2023 AND transcript LIKE "%bakery%";

-- Thief entered car in parking lot 10:15-10:25
-- Theif used atm earlier that morning (pre 10:15)
-- Theif called accomplice between 10:15-10:25 for less than 60s
-- Accomplice potentially bought tickets around this time for the earlier flight out of fifyville 7/29/23

-- Check bakery security logs for 10:15-10:25
SELECT activity, license_plate, minute FROM bakery_security_logs
WHERE year = 2023 AND month = 7
AND day = 28 AND hour = 10
AND minute BETWEEN 14 AND 26;

-- Cross reference license plates with people
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023 AND month = 7
    AND day = 28 AND hour = 10
    AND minute BETWEEN 15 AND 26
);

/*
List of potential thieves based on license plate
|Vanessa |
| Barry   |
| Iman    |
| Sofia   |
| Luca    |
| Diana   |
| Kelsey  |
| Bruce
*/

-- Look up flights for following day 7/29 from people who drove to bakery
SELECT airport_origin.city AS Origin, airport_destination.city AS Destination, people.name,
    flights.hour, flights.minute FROM flights
JOIN airports airport_origin ON flights.origin_airport_id = airport_origin.id
JOIN airports airport_destination ON flights.destination_airport_id = airport_destination.id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE passengers.passport_number IN (
    SELECT people.passport_number FROM people
    WHERE people.license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2023 AND month = 7
        AND day = 28 AND hour = 10
        AND minute BETWEEN 15 AND 26))
    AND airport_origin.city = "Fiftyville"
    AND flights.year = 2023 AND flights.month = 7
    AND flights.day = 29;

/* From the list of potential thieves based on licenses plates, these took a flight the next day:
+------------+---------------+--------+
|   Origin   |  Destination  |  name  |
+------------+---------------+--------+
| Fiftyville | Boston        | Diana  |
| Fiftyville | New York City | Sofia  |
| Fiftyville | New York City | Bruce  |
| Fiftyville | New York City | Kelsey |
| Fiftyville | New York City | Luca   |
+------------+---------------+--------+
*/

-- Check all phone call between 10:15-25 with a duration of less than 1min
SELECT caller_name.name "Potential Thief", receiver_name.name "Potential Accomplice" FROM phone_calls
JOIN people caller_name ON phone_calls.caller = caller_name.phone_number
JOIN people receiver_name ON phone_calls.receiver = receiver_name.phone_number
WHERE phone_calls.year = 2023 AND phone_calls.month = 7
AND phone_calls.day = 28 AND phone_calls.duration < 60;

/* These are the potential thieves and accomplices based on the phone calls under 60s
+-----------------+----------------------+
| Potential Thief | Potential Accomplice |
+-----------------+----------------------+
| Sofia           | Jack                 |
| Kelsey          | Larry                |
| Bruce           | Robin                |
| Kelsey          | Melissa              |
| Taylor          | James                |
| Diana           | Philip               |
| Carina          | Jacqueline           |
| Kenny           | Doris                |
| Benista         | Anna                 |
+-----------------+----------------------+
*/

-- Check atm withdrawals for 7/28 on Leggett
SELECT people.name, amount FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE transaction_type = "withdraw" AND atm_location LIKE "Legget%"
AND month = 7 AND day = 28;

/* People who withdrew money from their atm on Leggett on 7/28
+---------+--------+
|  name   | amount |
+---------+--------+
| Bruce   | 50     |
| Diana   | 35     |
| Brooke  | 80     |
| Kenny   | 20     |
| Iman    | 20     |
| Luca    | 48     |
| Taylor  | 60     |
| Benista | 30     |
+---------+--------+
*/

-- Search for names that made a < 60s call, got on a flight, the next morning, withdrew from atm in prior to theft, and drove

SELECT people.name FROM people
WHERE people.name IN (
        -- Check atm withdrawals for 7/28 on Leggett
    SELECT people.name FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
    WHERE transaction_type = "withdraw" AND atm_location LIKE "Legget%"
    AND month = 7 AND day = 28)
AND people.name IN (
    -- Look up flights for following day 7/29 from people who drove to bakery
    SELECT people.name FROM flights
    JOIN airports airport_origin ON flights.origin_airport_id = airport_origin.id
    JOIN passengers ON passengers.flight_id = flights.id
    JOIN people ON people.passport_number = passengers.passport_number
    WHERE passengers.passport_number IN (
        SELECT people.passport_number FROM people
        WHERE people.license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2023 AND month = 7
            AND day = 28 AND hour = 10
            AND minute BETWEEN 15 AND 26))
        AND airport_origin.city = "Fiftyville"
        AND flights.year = 2023 AND flights.month = 7
        AND flights.day = 29)
AND people.name IN (
    -- Check atm withdrawals for 7/28 on Leggett
    SELECT people.name FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
    WHERE transaction_type = "withdraw" AND atm_location LIKE "Legget%"
    AND month = 7 AND day = 28)
AND people.name IN (
    -- Check all phone call between 10:15-25 with a duration of less than 1min
    SELECT caller_name.name "Potential Thief" FROM phone_calls
    JOIN people caller_name ON phone_calls.caller = caller_name.phone_number
    WHERE phone_calls.year = 2023 AND phone_calls.month = 7
    AND phone_calls.day = 28 AND phone_calls.duration < 60);

/* Only two people fit this description:
+-------+
| name  |
+-------+
| Diana |
| Bruce |
+-------+
However, Diana took the later flight and Bruce was on the morning flight, leaving Bruce as the prime suspect.
This also leaves Robin as the accomplice.
