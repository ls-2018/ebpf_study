Vagrant.configure("2") do |config|
  (1..3).each do |i|
    config.vm.define "k8s-node#{i}" do |done|

      config.vm.hostname = "k8s-node#{i}"

      config.ssh.username = "vagrant";
      config.ssh.password = "vagrant";
      config.ssh.insert_key = true;

      config.vm.box = "acejilam/ubuntu22.04"

      # Disable automatic box update checking. If you disable this, then
      # boxes will only be checked for updates when the user runs
      # `vagrant box outdated`. This is not recommended.
      # config.vm.box_check_update = false

      # Create a forwarded port mapping which allows access to a specific port
      # within the machine from a port on the host machine. In the example below,
      # accessing "localhost:8080" will access port 80 on the guest machine.
      # NOTE: This will enable public access to the opened port
      # config.vm.network "forwarded_port", guest: 80, host: 8080

      config.vm.network "private_network", ip: "192.168.33.#{i + 10}"

      config.vm.synced_folder "./data", "/vagrant_data"
      config.vm.synced_folder "./repo", "/etc/apt" , disabled: true

      config.vm.provider "virtualbox" do |vb|
        vb.name = "k8s-node#{i}"
        vb.gui = false
        vb.cpus = "4"
        vb.memory = "5120"
      end

      config.vm.provision "shell", inline: <<-SHELL
        echo -e 'root\nroot\n'|passwd root
        echo 'nameserver 114.114.114.114' > /etc/resolv.conf
        apt-key adv --keyserver keyserver.ubuntu.com --recv 871920D1991BC93C
        apt clean all
        apt-get update -y
        apt-get install -y apache2
        apt-get install -y make clang llvm libelf-dev libbpf-dev bpfcc-tools libbpfcc-dev linux-tools-$(uname -r) linux-headers-$(uname -r)
      SHELL
    end
  end
end
