fn main()
{
	let mut total = 0;

	for i in 0..10000000
	{
		if i % 2 == 0
		{
			total += 1;
		}
	}

	println!( "total : {}", total );
}
