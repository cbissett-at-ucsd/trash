from wsgiref.simple_server import make_server
from pyramid.config import Configurator
from pyramid.response import Response
from pyramid.renderers import render_to_response

import requests
import os
import json

from random import *

def hello_world(request):
    return Response("hello")

def double(req):
    page_data = req.GET.mixed()
    print("extracted ID")
    print(int(page_data['id']))
    return Response(str(randint(0,1)))

def get_form(req):
    return render_to_response('form.html', {}, request=req)


if __name__ == '__main__':
    i=0
    print("connected")
    config = Configurator()
    config.include('pyramid_jinja2')
    config.add_jinja2_renderer('.html')

    config.add_route('hello', '/')
    config.add_view(hello_world, route_name='hello')

    config.add_route('form','/form')
    config.add_view(get_form,route_name='form')

    config.add_route('double', '/double')
    config.add_view(double, route_name='double', request_method='GET')


    app = config.make_wsgi_app()
    server = make_server('0.0.0.0', 6543, app)
    server.serve_forever()