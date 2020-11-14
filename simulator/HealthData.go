package simulator

//HealthData struct
type HealthData struct {
	ticksSinceInfection int

	isInfected bool
	isMobile   bool
	isCured    bool
	isDead     bool
	inHospital bool

	//Individual survival chance required for simulating hospitals
	//TODO base this on risk groups (age)?
	survivalChance float64
}

func (data HealthData) Infected() bool {
	return data.isInfected
}

func (data HealthData) Mobile() bool {
	return data.isMobile
}

func (data HealthData) Cured() bool {
	return data.isCured
}

func (data HealthData) Dead() bool {
	return data.isDead
}

func (data HealthData) Hospitalized() bool {
	return data.inHospital
}
