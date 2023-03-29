<a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cl4qxms4g001609l49j835g66/project/3038270" alt="joslopez's 42 Philosophers Score" /></a>
<!DOCTYPE html>
<html>
  <body>
    <h1>Overview</h1>
    <p>Here are the things you need to know if you want to succeed this assignment:</p>
    <ul>
      <li>One or more philosophers sit at a round table.</li>
      <li>There is a large bowl of spaghetti in the middle of the table.</li>
      <li>The philosophers alternatively eat, think, or sleep.
        <ul>
          <li>While they are eating, they are not thinking nor sleeping;</li>
          <li>while thinking, they are not eating nor sleeping;</li>
          <li>and, of course, while sleeping, they are not eating nor thinking.</li>
        </ul>
      </li>
      <li>There are also forks on the table. There are as many forks as philosophers.</li>
      <li>Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.</li>
      <li>When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.</li>
      <li>Every philosopher needs to eat and should never starve.</li>
      <li>Philosophers don’t speak with each other.</li>
      <li>Philosophers don’t know if another philosopher is about to die.</li>
      <li>No need to say that philosophers should avoid dying!</li>
    </ul>
    <h1>Global Rules</h1>
	<p>You have to write a program for the mandatory part and another one for the bonus part (if you decide to do the bonus part). They both have to comply with the following rules:</p>
	<ul>
		<li>Global variables are forbidden!</li>
		<li>Your(s) program(s) should take the following arguments:</li>
		<ul>
			<li>number_of_philosophers</li>
			<li>time_to_die (in milliseconds)</li>
			<li>time_to_eat (in milliseconds)</li>
			<li>time_to_sleep (in milliseconds)</li>
			<li>[number_of_times_each_philosopher_must_eat]</li>
			<ul>
				<li>number_of_philosophers: The number of philosophers and also the number of forks.</li>
				<li>time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.</li>
				<li>time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.</li>
				<li>time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</li>
				<li>number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.</li>
			</ul>
		</ul>
		<li>Each philosopher has a number ranging from 1 to number_of_philosophers.</li>
		<li>Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.</li>
	</ul>
  </body>
</html>
