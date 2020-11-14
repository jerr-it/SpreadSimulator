package backends

type IBackend interface {
	Run()
	SaveStats(string)
}
