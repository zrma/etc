# things.py

# Let's get this party started!
import falcon


# Falcon follows the REST architectural style, meaning (among
# other things) that you think in terms of resources and state
# transitions, which map to HTTP verbs.
class ThingsResource:
    def on_get(self, _, res):
        """Handles GET requests"""
        res.status = falcon.HTTP_200  # This is the default status
        res.body = ('\nTwo things awe me most, the starry sky '
                    'above me and the moral law within me.\n'
                    '\n'
                    '    ~ Immanuel Kant\n\n')


# falcon.API instances are callable WSGI apps
app = falcon.API()

# Resources are represented by long-lived class instances
things = ThingsResource()

# things will handle all requests to the '/things' URL path
app.add_route('/things', things)
