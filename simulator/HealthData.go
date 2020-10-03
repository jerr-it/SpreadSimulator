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
