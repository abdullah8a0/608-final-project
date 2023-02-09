# 608-final-project

<meta charset="utf-8" emacsmode="-*- markdown -*-">

**Profemon - Final Report**

In our project, we implemented a dynamic, pvp, in-person turn-based fighting game similar to Pokemon Go. Players can “capture” professors by scanning their MIT ID, which forces them to go around finding and interacting with professors, allowing them to know their professors better. After a “Profemon” is captured, it will be stored in a database on a server to recognize the player as having captured that Profemon, so players can use the corresponding Profemon in pvp battles. In these battles, players meet up physically to pair using WiFi concurrent access point station mode, then select their profemons and battle it out! The battle calculations are done on the server after the server has received moves from both players. Once the server has heard back from both players, the devices will receive the updated game state by periodically querying the server.

[![Full System Video](https://img.youtube.com/vi/48xc-4H155g/0.jpg)](https://www.youtube.com/watch?v=48xc-4H155g)

Functionality
===============================================================================
The system starts in a menu selection screen where the player selects either Capture mode or Battle mode using the joystick.


Capture Mode
-------------------------------------------------------------------------------
A Profeball in Capture mode will use the in-system RC522 module to read RFID cards. To read a card, simply hold the card against the visible RC522 in the top half of the Profeball for a couple of seconds. Upon successfully reading the card, the screen will update with the capture status. To exit capture mode, simply press the joystick button again.
TODO: Add an image here of the reader

Battle Mode
-------------------------------------------------------------------------------
Battle mode starts off with the screen telling the player that they are about to enter pairing mode. Upon pressing the joystick button, the player will enter Pairing Mode (more details below). After successfully pairing, both players in the battle will be able to select one of their captured Profemon to battle with.
	Throughout the battle, the player’s device will repeatedly query the server for the status of the game, as well as sending the player’s move once per turn. The UI will update to display attacks happening, along with any changes to HP. When either Profemon’s HP points reach zero, the battle is over and either player will receive a message telling them whether they’ve won or lost.
	After a battle, a player will return to the main screen through a joystick press, and can battle or capture more Profemon.


Pairing Mode
-------------------------------------------------------------------------------
![Pairing FSM](https://i.imgur.com/DwqP3Mp.png)

For a successful pairing between two players, one of them selects to broadcast their ID, while the other one listens. This done at the start of paring by selecting one of two modes of pairing, “Listen” or “Broadcast”. The listener stops as soon as it finds an ID, it then sends the server a request to start a game.

The broadcast mode broadcasts its ID for 10 seconds before asking the server if anyone has sent a start game request. Once this is done, the server and the two players know the game ID generated by the server and we can start the game.

Documentation
===============================================================================

Hardware Layout
-------------------------------------------------------------------------------
### Hardware Diagram

![Wiring in Profeball](https://i.imgur.com/XJFb958.png)
Here you see a wiring of the entire Profeball including all the connections between modules and the ESP32.

### 3D Printed Profeball
The Profeball design was obtained from Thingiverse at this [link](https://www.thingiverse.com/thing:1615753). The design was scaled to 175% of its original size to accommodate the breadboard and electronics. The Profeball can be opened in this design by MrFozzie because they take advantage of the natural flex of the plastic to make a press release latch.
[Image of Exploded View of Profeball from Thingiverse](https://cdn.thingiverse.com/renders/26/57/60/a5/0b/5230c078de22f1c9ec2a18fa673ff8a5_preview_featured.JPG)

### Laser-cut Plates
In order to keep the inside of the Profeball organized, we designed and lasercut 0.125 inch acrylic plates with holes for mounting and cutouts for the solder points on the modules. There are three of these plates:
![Parts for Profeball](https://i.imgur.com/draj7un.jpg)

The first plate (rightmost)  fits into the top of the Profeball. The RC522 is mounted to it, and there circular hole is for avoiding collision with the joystick.

The second plate (middle) fits level with the rim of the Profeball. The ST7735 (screen) is mounted to it, and there is a large hole for the joystick to stick through and move. The buzzer is also mounted on this level in a hole that just barely fits it without crushing. The transistor (2N3904) and 3.6K ohm resistor are taped to the top of this plate to keep them out of the way of the rest of the wiring.

The third plate (leftmost) fits into the Profeball below the second plate. The joystick is mounted on this level to keep much of the base of the module out of the player’s way. There is a hole for the buzzer wires to fit through on this level as well.

Parts List
-------------------------------------------------------------------------------
[RC522 RFID Reader](https://www.amazon.com/SunFounder-Mifare-Reader-Arduino-Raspberry/dp/B07KGBJ9VG/ref=sr_1_3?crid=3E4UBP33IURKH&keywords=rc522&qid=1652038519&sprefix=rc522%2Caps%2C232&sr=8-3)

* Total price: $7.99
* Use case: Used to read RFID signals for capturing Profemon.

[Joysticks 6 pcs](https://www.amazon.com/Joystick-Game-Controller-Dual-axis-Compatible-Electronic/dp/B094HRM72Z/ref=sr_1_2_sspa?crid=1E9EP8LU39009&keywords=joystick+arduino&qid=1652038728&sprefix=joystick+arduino%2Caps%2C95&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzT0YwRTNaNU1ZNzdWJmVuY3J5cHRlZElkPUEwMDI3NjM1N0JIUFhRU0wxSDFMJmVuY3J5cHRlZEFkSWQ9QTA2NDA1ODEyM0FKQjhMMjRYV1VXJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
Total price: 10.99
Use case: Used to navigate the UI.

[Compact 5000mAhBattery Pack](https://www.amazon.com/dp/B08T8TDS8S/ref=emc_b_5_t)
Total price: $13.99
Use case: Used to provide power for the Profeball without needing to connect it to a computer. The power lasts for about 3 days.

Lab Provided Parts:
ESP32S2 Dev Module
Buzzer
3.6K Ohm resistor
ST7735 LED Display
Jumper Cables
Breadboard


Design Challenges and Decisions
-------------------------------------------------------------------------------
Some challenges in this project included:
* Dynamically storing image files
* Synchronizing the status across the server and the two devices
* Fitting all of the needed components inside of the Profeball

### Dynamically storing image files
Since for each battle, the player needs to select a Profemon from their collection, which is updated whenever a new capture is made, the images are stored on the server, which allows for easy retrieval and modification. Whenever the user needs to select a Profemon, the server sends the image data in a base64 encoded string along with the image size, then the device side code dynamically assigns memory for storing these images, which is freed after the selection stage. In this way, starting a game multiple times does not add to the memory usage, since the memory for storing the images is freed each time.

### Synchronizing the status across the server and the two devices
For each step in the battle, the device sends the move to the server and starts querying the server for status updates in regular intervals. Once the server receives moves selected by both players, it does the calculations of the damage and then returns the json files containing the game status to each device when the device queries the server for the update. Note that the json files returned to the players are device-centric, meaning that for each device, the value contained in e.g. `player_hp` is the value for their profemon, so the device does not need to do further parsing to determine which one of the values is the player versus the opponent.

### Packing Electronics in Profeball
Even with the Profeball scaled to 175% of its original size (a 3D print that took over 72 hours per Profeball in optimal conditions), the Profeball still struggled to fit the parts we wanted. To make our limit volume work, we dremeled off the part of the inner Profeball frame (the black lattice) that collided with the battery pack and the breadboard. Additionally, the jumper cable connectors also provided additional height that made fitting electronics into the bottom half difficult. To solve this issue, we cut the connectors on the breadboard side off, and stripped and tinned the wires so they would go directly into the breadboard. Then, since the wires were now in more danger of pulling out, we added a dab of hot glue on top of the connections to secure them.
###
###

Detailed Code Layout
===============================================================================

ESP32 Side
-------------------------------------------------------------------------------
![ESP32 Side FSM Diagram](https://i.imgur.com/CMw6HVS.png)
### Imported libraries
We make use of a few support files `http_req.h`, `http_req.cpp` to send and receive HTTP requests, and `util.h`, `util.cpp` for easier read-in of the joystick values. We use the `renderjpeg.h` file for rendering jpeg images, taken from the examples of the `TFT_eSPI` library by Bodmer. The libraries we used outside of the basic setup include
- `ArduinoJson` library for parsing JSON files received from the server
- `JPEGDecoder` library for decoding the jpeg images
- `base64` library for decoding base64 strings received from the server which encodes the images
- `MFRC522` library for reading RFID cards


#### Joystick Interface

A joystick class can be instantiated using `Joystick(int VRx, int VRy, int Sw, int button_mode, int joystick_mode)`. The button_mode determines whether the button is a Button class (mode 0) or an edge detector (mode 1). The edge detection returns 1 on rising edges, -1 on falling edges and 0 otherwise.

The joystick_mode determines the format of the returned value that the joystick gives regarding its direction. In mode 0, the joystick simply returns its current direction as an enum. In mode 1, We return the direction but only after `JOYSTICK_DELAY` amount of time has passed since the last return. So if the Joystick delay is 3 cycles and the joystick points up, the return value looks like: `UP NONE NONE NONE UP NONE NONE NONE UP`. This is used for better GUI responsiveness.

### Important functions
#### Buzzer audio
- `Riff make_riff(int8_t *d, int length, double duration)`: take in an array of integers, the length of the array, and the duration of each note in millisecond, and outputs a riff struct consisting of the array in raw frequencies.
- `void play_riff(int8_t* notes_song_to_play, int length_of_song, double duration)`: takes in the same inputs as `make_riff`, calls `make_riff` to make a riff struct, and plays the riff using `ledcWriteTone`.

#### Capturing a Profemon
- `void catch_request(char *uid, char *RESPONSE)`: takes in the uid of the card and a buffer to store the response from the server. Then, it scans the network for WiFi networks and uses the google geolocation API to get the latitude and longitude of the capture location. It then sends the uid and the location of capture to the server. The server response is then stored in the buffer to be displayed.

#### Pairing with another device
- `bool broadcast(char *my_id)`: Turns on the WiFi Access point mode on the ESP32, with the WiFi SSID ‘Profemon’+my_id. It then waits for `HOSTING_TIMEOUT_MS` milli seconds and returns.
- `bool listen(char *other_id)`: It scans the current open WiFi APs and finds if there are any that start with the 8 character string ‘Profemon’. If it finds such an SSID, it copies the id in the SSID into `*other_id` and returns true. At any point of failure returns false.
- `void post_ids(char *my_id, char *other_id)`: Crafts an HTTP request and sends it to server which updates the server on the successful finding of an opponent, the server then generates a unique game_id and saves that in the database.
- `bool sync_ids(char *my_id, char *game_id)`: Crafts and sends an HTTP request to the server which responds with the game_id the player is in. This is used by both the listener and broadcaster to get their game IDs.
- `bool connect_wifi()`: Connect to MIT Guest wifi, this is used in case we disconnect during the pairing cycle.

#### Selecting a Profemon for battle
- `bool user_has_profemons()`: queries the server first to see if the user has any profemons. If not, it displays a message on the TFT to the user and returns false. If the user has profemons, it returns true.
- `void get_profemons()`: gets the profemons from the server. First, it queries the server for the length of the response by including a flag `len=true` in the request. Then, it uses `calloc` to dynamically assign the memory for the response. Then, it sends the request to the server, and receives the response. The response is then parsed using `deserializeJson()`, which contains the number of profemons, the name, image (encoded in base64), and image size for each profemon. The number of profemons is stored in `profemon_count`, and then `calloc` is used to dynamically assign the memory for the profemon images. The names and images (after decoding the base64 string) of profemons are then stored in global variables, and the response is freed.
- `void select_profemon(uint8_t i)`: displays the profemon's image and name whose index is `i` on the TFT.
- `void send_selection(uint8_t i)`: sends the `i`th profemon's name to the server along with username and game id.

#### Battle
- `bool battle_init()`: queries the server for battle initialization information. Similarly, we first query for length. If the server returns a string with `wait` in it, returns `false`. Otherwise, use `calloc` to dynamically assign the memory for the response. Then, we send the request to the server, and receive the response. The response is then parsed using `deserializeJson()`, which contains the player and the opponent's images along with the sizes and the maximal hp values, as well as the names of the player's moves. These are then stored in global variables in a similar fashion, and the response is freed.
- `void display_hp()`: displays the player's and opponent's hp on the TFT by drawing layers of rectangular bars. The fraction of the hp is calculated using the current hp and the maximal hp. The bar is first completely filled with either black or red, and the opposite color is drawn on top with proper proportions. Finally, the white border is drawn on top.
- `void display_battle()`: displays the player's and opponent's images on the TFT as well as the hp values through calling `display_hp()`.
- `bool battle_step()`: queries the server for updated battle information. Returns `false` if server returns a string with `wait`, which implies the server is waiting for the opponent to move. Otherwise, parse the json response and store the new hp values and the display texts in global variables.

###

Server Side
-------------------------------------------------------------------------------
This figure shows some of the most important parts of our server side elements:
**********************************************************
*            Server-side                                 *
*  .------------------------------.                      *
* |     /                          |                     *
* |     |                          |                     *
* |     +-- jsons/                 |                     *
* |     |                          |                     *
* |     +-- images/                |                     *
* |     |                          |                     *
* |     +-- profemon.db            |                     *
* |     |   |                      |                     *
* |     |   +-- catch              |                     *
* |     |   +-- moves              |                     *
* |     |   +-- profemon           |                     *
* |     |                          |                     *
* |     +-- battle.db              |                     *
* |     |   |                      |                     *
* |     |   +-- meta               |                     *
* |     |   +-- move               |                     *
* |     |                          |                     *
* |     +-- catch.py               |                     *
* |     +-- battle.py              |                     *
* |     +-- get_profemon.py        |                     *
* |     +-- tests.py               |                     *
*  '------------------------------'                      *
**********************************************************

### jsons
This folder has the display info to be fetched by the client side. They look like this:
```json
{'move1': {'player_hp': 108, 'opponent_hp': 53, 'display_text': 'JoeSteinmeyer used Sludge Bomb'}, 'move2': {'player_hp': 71, 'opponent_hp': 53, 'display_text': 'SaraEllison used Absolute Zero'}}
```
Where the client side is given two HP values for displaying both the player and their opponent’s Profemon HP.

### images
This folder has all the jpg photos of the professors. It is used by get_profemon.py to pass them to the client side.

### profemon.db
Contains general information about profemons and their owners. It has three tables: catch, moves, and profemon.

#### catch
The Catch table contains information about captures. The ESP32 uploads to this table when the user scans a professor’s ID. The server uses this to determine what profemon(s) a user has.

| user | uid         | lat       | lon        | time                       | name          |
|------|-------------|-----------|------------|----------------------------|---------------|
|  42  | 93 41 30 A7 | 42.354959 | -71.101669 | 2022-04-20 03:35:01.294567 |   AdamHartz   |
| 20   | 1E 7F 71 A6 | 42.358643 | -71.094491 | 2022-04-26 02:54:29.866097 | PattiChristie |

#### moves

Moves contains information about Profemon moves/attacks. When an attack is selected, the server uses this table to look up the power and hit rate of the attack. This is used to determine if the move hits, and how much damage is inflicted if it does. A sample of the table is below. Having a separate table allowed us to recycle moves across unique Profemon.

| name        | phy or spec | type     | power | hit rate |
|-------------|-------------|----------|-------|----------|
| Helix Punch | phy         | fighting | 100   | 0.8      |
| Sequence    | phy         | physic   | 60    | 0.95     |
| Tri-Attack  | spec        | electric | 60    | 0.95     |
| Fold        | phy         | psychic  | 100   | 0.5      |

### profemon
Profemon contains information about Profemon stats and the ID associated with each one. When a Profemon is captured, the server uses this table to look up the name associated with the ID. During a battle, the server looks up the Profemon’s available attacks from this table. A sample of the table is below.
|cipher     |name             |hp |atk|def|spatk|spdef|spd|move1       |move2       |move3        |move4      |
|-----------|-----------------|---|---|---|-----|-----|---|------------|------------|-------------|-----------|
|0E 14 4B A6|JoeSteinmeyer    |108|68 |53 |63   |63   |103|Double Team |Volt Switch |Signal Beam  |Confuse    |
|0E 3E 4B A6|AdamHartz        |128|83 |68 |53   |68   |98 |Fury Swipes |Astonish    |Recurse      |Bind       |
|1E 7F 71 A6|PattiChristie    |93 |23 |243|23   |243  |18 |Hyper Voice |Sludge Bomb |Absolute Zero|Confuse    |
|43 81 40 86|SaraEllison      |133|68 |68 |58   |58   |73 |Future Sight|Confuse     |Optimize     |Clear Fog  |
|8D BB 6D D5|MohamedAbdelhafez|113|68 |93 |48   |73   |43 |Gravity     |Flash Cannon|Magnet Beam  |Confuse    |

### battle.db
Database that handles all of the battle states.
#### meta
Table used to store the current state of battles with a row for each battle ID. The row is updated whenever a turn happens in a battle, and when a battle is completed, the row is removed. “user1” and “user2” refer to player IDs. name1 and name2 refer to Profemon names.

|game_id|user1|name1|user2|name2|hp1|hp2|
|--------|--------|---------|-------------|---|---|---|
|20|20|SaraEllison|42|JoeSteinmeyer|9|108|

#### move
Table used to store a user’s action until their opponent has responded. For every battle, only one action can be stored at a time. When the server receives a move associated with a particular battle ID, and there also exists an action in the table, the server will know that it should calculate damages, update meta and move, and return values to the players.

### catch.py
It handles the capture request sent by the ESP32.
![catch state diagram](https://i.imgur.com/iGhwaTa.png)

### battle.py

When two players are paired, they send POST request with their game_id to the server. The game creation process is handled as below:

![join state diagram](https://i.imgur.com/sTTisUs.png)

When every turn the two players send a move to the server, to which the server responds with the hp values of the profemons after the moves are made, stored in json files.
![move state diagram](https://i.imgur.com/I7Ssrwa.png)


Milestone Contributions
===============================================================================

## Hardware
![Showing RFID scanner working](https://youtu.be/3OeNl7Hbbhg)
![Profeball! Printed](https://s7.gifyu.com/images/profeball.gif)
![Assembled Profeball Tour](https://www.youtube.com/watch?v=zVC25HnnGds)

## Software
![Rudimentary state machine skeleton with local images](https://youtu.be/0iA528hKyPs)
![Capturing demonstration with Postman](https://youtu.be/3OeNl7Hbbhg)
![Pairing demonstration with hotspot](https://youtu.be/-b_8f32p_zI)
![Integrated system with minor bugs](https://youtu.be/0OERUU5kmrU)
![Integrated system without sound effects](https://youtu.be/xul82FiG2Hg)
![Profemon in server](https://i.imgur.com/FZ1gQWF.mp4)

Team Members
===============================================================================

* Muhammad Abdullah
* Heidi Lei
* Andi Liu
* Ivy Liu

<!-- Markdeep: --><style class="fallback">body{visibility:hidden;white-space:pre;font-family:monospace}</style><script src="markdeep.min.js" charset="utf-8"></script><script src="https://casual-effects.com/markdeep/latest/markdeep.min.js?" charset="utf-8"></script><script>window.alreadyProcessedMarkdeep||(document.body.style.visibility="visible")</script>



