import boto3
client = boto3.client('ec2')

response = client.describe_regions(
	Filters=[
		{
			'Name': 'string',
			'Values': [
				'string',
			]
		},
	],
	RegionNames=[
		'string',
	],
	DryRun=True|False
)

print(response)
