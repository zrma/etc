import {createClient} from '@supabase/supabase-js'

const supabaseUrl = process.env.SUPABASE_URL ?? 'http://127.0.0.1:54321';
const supabaseAnonKey = process.env.SUPABASE_ANON_KEY ?? 'test-anon-key';

// Supabase 인증 라우트에서 재사용할 샘플 클라이언트
const sb = createClient(supabaseUrl, supabaseAnonKey)

export default sb
