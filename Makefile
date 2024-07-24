clean:
	find ./case -name "*.json" |xargs -I F rm -rf F
	find ./case -name "*.o" |xargs -I F rm -rf F