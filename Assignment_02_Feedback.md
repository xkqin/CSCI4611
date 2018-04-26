### Feedback for Assignment 02

Run on March 14, 20:36:10 PM.

+ Pass: Change into directory "dev/a2-carsoccer".

+ Pass: Make directory "build".

+ Pass: Change into directory "build".

+ Pass: Copy directory "Google Tests".

    Copied directory.



+ Pass: Setup Testing

    Complete.



+ Pass: Check that CMake Configures.

    CMake configures with no errors.



+ Pass: Check that make compiles.

    Make compiles with no errors.



+ Pass: Check that a GoogleTest test passes.
    passes the test: CarSoccer.InitBall.



+ Fail: Check that a GoogleTest test passes.
    fails the test: CarSoccer.BallUpdate.
<pre>
[ RUN      ] CarSoccer.BallUpdate
/class/grades/Spring-2018/csci4611/student-repos/Assignment_02_Feedback/repo-qinxx215/dev/a2-carsoccer/gtests/main.cc:84: Failure
Expected: (0.00001f) <= (-acceleration[1]), actual: 1e-05 vs -16.118
<b>There should be a downward acceleration due to gravity.</b></pre>



+ Pass: Check that a GoogleTest test passes.
    passes the test: CarSoccer.BallBounce.



+ Pass: Check that a GoogleTest test passes.
    passes the test: CarSoccer.BallWallBounce.



+ Fail: Check that a GoogleTest test passes.
    fails the test: CarSoccer.CarMovement.
<pre>
[ RUN      ] CarSoccer.CarMovement
/class/grades/Spring-2018/csci4611/student-repos/Assignment_02_Feedback/repo-qinxx215/dev/a2-carsoccer/gtests/main.cc:246: Failure
Expected: (0.00001f) > (carVel.Length()), actual: 1e-05 vs 0.0237503
<b>The car should not move to the side without thrust.</b></pre>



