"""
./SpreadSimulation 5000 5 4750 200 10 450 20 50 50 5 true 4 600 600 1000 8 | python StatRenderer.py

Stdin:
tick susceptible infected cured dead hospitalized R0 Re
"""

import sys
import matplotlib.pyplot as plt

ticks = []
stats = {
    "Susceptible": [],
    "Infected": [],
    "Cured": [],
    "Dead": [],
}

hospitalized = []

rs = {
    "R0": [],
    "Re": []
}

for line in sys.stdin:
    dataSegments = line.split(" ")

    ticks.append(int(dataSegments[0]))

    stats["Susceptible"].append(int(dataSegments[1]))
    stats["Infected"].append(int(dataSegments[2]))
    stats["Cured"].append(int(dataSegments[3]))
    stats["Dead"].append(int(dataSegments[4]))
    hospitalized.append(int(dataSegments[5]))

    rs["R0"].append(float(dataSegments[6]))
    rs["Re"].append(float(dataSegments[7]))

fig, ax = plt.subplots(1)

ax.stackplot(ticks, stats.values(), labels=stats.keys())
ax.legend(loc="upper right")
ax.set_title("Simulation")
ax.set_xlabel("Tick")
ax.set_ylabel("Count")

fig2 = plt.figure()
gs = fig2.add_gridspec(2, hspace=0)
(ax2, ax3) = gs.subplots(sharex=True)

ax2.plot(ticks, rs["R0"])
ax2.set_xlabel("Tick")
ax2.set_ylabel(r"$R_0$")
ax2.set_title(r"$R_0/R_e$")

ax3.plot(ticks, rs["Re"])
ax3.set_xlabel("Tick")
ax3.set_ylabel(r"$R_e$")

fig3, ax4 = plt.subplots(1)
ax4.plot(ticks, hospitalized)
ax4.legend(loc="upper right")
ax4.set_title("Hospitalized")
ax4.set_xlabel("Tick")
ax4.set_ylabel("Hospitalized")

plt.show()
