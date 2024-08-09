Vagrant.configure("2") do |config|
    config.vm.box = "bento/ubuntu-22.04"
    config.vm.provision "ansible_local" do |ansible|
        ansible.playbook = "provision.yaml"
    end
end