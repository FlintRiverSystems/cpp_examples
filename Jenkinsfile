pipeline
{
	agent 
	{
		label 'VS2017'
	}
 
	stages
	{
		stage('build')
		{
			steps
			{
				bat 'python build.py'
			}
		}
	}

	post
	{
		success 
		{
			mail body: 'EOM', from: 'jenkins@flintriversystems.com', subject: "Job ${env.JOB_NAME} (${env.BUILD_NUMBER}) success", to: 'reporting@flintriversystems.com'
		}
		failure 
		{
			mail body: 'EOM', from: 'jenkins@flintriversystems.com', subject: "Job ${env.JOB_NAME} (${env.BUILD_NUMBER}) failed", to: 'reporting@flintriversystems.com'
		}
	}
}
	
