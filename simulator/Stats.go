package simulator

import "fmt"

//Statistic holds information about current and past infection related numbers
//TODO export as CSV
type statistic struct {
	Susceptible  []uint
	Infected     []uint
	Cured        []uint
	Dead         []uint
	Hospitalized []uint
}

//NewStats creates a new stat object
func newStats() statistic {
	return statistic{
		make([]uint, 0),
		make([]uint, 0),
		make([]uint, 0),
		make([]uint, 0),
		make([]uint, 0),
	}
}

func (stat *statistic) newColumn() {
	stat.Susceptible = append(stat.Susceptible, 0)
	stat.Infected = append(stat.Infected, 0)
	stat.Cured = append(stat.Cured, 0)
	stat.Dead = append(stat.Dead, 0)
	stat.Hospitalized = append(stat.Hospitalized, 0)
}

func (stat *statistic) setCurrent(s, i, c, d, h uint) {
	currentIdx := len(stat.Susceptible) - 1

	stat.Susceptible[currentIdx] = s
	stat.Infected[currentIdx] = i
	stat.Cured[currentIdx] = c
	stat.Dead[currentIdx] = d
	stat.Hospitalized[currentIdx] = h
}

func (stat *statistic) print() {
	fmt.Printf("Susceptible: %d, Infected: %d, Cured: %d, Dead: %d, Hospital: %d\n",
		stat.Susceptible[len(stat.Susceptible)-1],
		stat.Infected[len(stat.Infected)-1],
		stat.Cured[len(stat.Cured)-1],
		stat.Dead[len(stat.Dead)-1],
		stat.Hospitalized[len(stat.Hospitalized)-1])
}
