<h1 align="center">SpreadSimulator</h1>

<p align="center">
    <img src="https://img.shields.io/badge/-Golang-blue?style=for-the-badge&logo=go" />
</div>

<br>

<p align="center">
Simulation of the spread and containment of infections
</p>

<h2 align="center">
    New
</h2>
<p align="center">
Complete rework in <b>Go</b>.
For the old C version, see the legacy zip file.
</p>

## Run
Requires https://github.com/veandco/go-sdl2
```
go build
./SpreadSimulator [options]
```
The following options are available;
1. -cfg [filame] | Choose a configuration by its filename, will use 'standard' if omitted
2. -v | Log current statistics in console
3. -export | Saves the statistics into the export directory as a CSV-File

<i> Example calls </i>
```
./SpreadSimulator -v
./SpreadSimulator -cfg customConfig -v
./SpreadSimulator -v -export
./SpreadSimulator -cfg customConfig -export
```


## TODO
1. ~~Config via JSON~~
2. ~~Statistics export using CSV~~
3. ~~CLI Options/Flags~~
4. NoGUI option
5. (Live?) Visual Statistics
6. More Rendering Backends
7. ???
8. Profit

## How it works
In the following text the phrase within parenthesis will be a reference to above code snippets comments.  
The simulator creates a given number of entities(samples) within a confined space(Area of movement).  
Each of them is given a randomized motion vector, which is added to their position every tick.   
A number of them will be infected at the start(initial infected).  
A number of them will be able to move around(mobile entities).
If another entity passes within a given radius(radius of influence in pixels), it'll get infected by a certain probability(chance of infection upon contact).  
When an entity gets infected a timer will start. As soon as this timer runs out, the entity will either survive or die by a certain percentage(chance of surviving).  
The hospital capacity(hospital capacity) determines how many hospital slots are available to the infected.  
Each tick a number of random entities(tests per tick) will be tested and detected using a certain probability(detection chance).  
In the case of an entity getting a positive test result, meaning he will be hospitalized, he won't be able to move anymore and its chance of surviving is set to 90%.
If active social distancing is set to true, the entities will try actively try to avoid each other.
Randomly placed central locations attract entities during opening hours and repell them during closing time.
