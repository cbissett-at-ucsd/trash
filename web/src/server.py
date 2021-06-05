from wsgiref.simple_server import make_server
from pyramid.config import Configurator
from pyramid.response import Response


def hello_world(request):
    return Response('Hello World!')

def double(request):
    x=request.get('int')
    x=x*2
    return Response(x)


if __name__ == '__main__':
    with Configurator() as config:
        config.add_route('hello', '/')
        config.add_view(hello_world, route_name='hello')

        config.add_route('hello', '/')
        config.add_view(hello_world, route_name='hello')

        config.add_route('double', '/double')
        config.add_view(double, route_name = 'double', request_method='GET')


        app = config.make_wsgi_app()
    server = make_server('0.0.0.0', 6666, app)
    server.serve_forever()