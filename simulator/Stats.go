package simulator

import (
	"encoding/csv"
	"fmt"
	"os"
)

//Statistic holds information about current and past infection related numbers
//TODO export as CSV
type statistic struct {
	statMatrix [][]uint
}

//NewStats creates a new stat object
func newStats() statistic {
	stats := make([][]uint, 6)

	for i := range stats {
		stats[i] = make([]uint, 0)
	}

	return statistic{
		stats,
	}
}

func (stat *statistic) GetHospitalCount() uint {
	currentIdx := len(stat.statMatrix[0]) - 1
	return stat.statMatrix[5][currentIdx]
}

func (stat *statistic) newColumn() {
	for i := range stat.statMatrix {
		stat.statMatrix[i] = append(stat.statMatrix[i], 0)
	}
}

func (stat *statistic) setCurrent(t, s, i, c, d, h uint) {
	currentIdx := len(stat.statMatrix[0]) - 1

	stat.statMatrix[0][currentIdx] = t
	stat.statMatrix[1][currentIdx] = s
	stat.statMatrix[2][currentIdx] = i
	stat.statMatrix[3][currentIdx] = c
	stat.statMatrix[4][currentIdx] = d
	stat.statMatrix[5][currentIdx] = h
}

func (stat *statistic) print() {
	currentIdx := len(stat.statMatrix[0]) - 1
	fmt.Printf("Susceptible: %d, Infected: %d, Cured: %d, Dead: %d, Hospital: %d\n",
		stat.statMatrix[1][currentIdx],
		stat.statMatrix[2][currentIdx],
		stat.statMatrix[3][currentIdx],
		stat.statMatrix[4][currentIdx],
		stat.statMatrix[5][currentIdx])
}

func (stat *statistic) SaveCSV(fileName string) {
	file, err := os.Create("./export/" + fileName + ".csv")
	if err != nil {
		panic(err)
	}

	csvWriter := csv.NewWriter(file)

	csvWriter.WriteAll(intToStringSlice(stat.statMatrix))

	csvWriter.Flush()

	file.Close()
}

func intToStringSlice(dat [][]uint) [][]string {
	res := make([][]string, len(dat))
	for i := range res {
		res[i] = make([]string, len(dat[i]))

		for j := range dat[i] {
			res[i][j] = fmt.Sprint(dat[i][j])
		}
	}

	res[0][0] = "Tick"
	res[1][0] = "Susceptible"
	res[2][0] = "Infected"
	res[3][0] = "Cured"
	res[4][0] = "Dead"
	res[5][0] = "Hospitalized"

	return res
}
