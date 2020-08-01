FROM rabbitmq:3.8.5

# Define environment variables.
ENV RABBITMQ_USER "example"
ENV RABBITMQ_PASSWORD "example"
ENV RABBITMQ_VHOST "example"

RUN rabbitmq-plugins enable rabbitmq_management

ADD ./init.sh /init.sh
RUN chmod +x /init.sh

# Define default command
CMD ["/init.sh"]
