import {createClient} from '@supabase/supabase-js'

// Create a single supabase client for interacting with your database
const sb = createClient('', '')

export default sb
