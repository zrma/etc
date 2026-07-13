import org.testng.annotations.Test
import kotlin.test.assertEquals

class MainTest {
    @Test
    fun testMultiply() {
        assertEquals(6, multiply(2, 3))
    }
}
